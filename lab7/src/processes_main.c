/*
 *  Race *race:
 *  This struct defines the state of the race, it contains various parameters
 *  which are explained in the race.h file
 *
 *  Basic idea: All process write(read) to(from) the reporter. So if any information
 *  has to be passed to the hare from the turtle, the turtle sends the information
 *  to the reporter and the reporter forwards it to hare. All synchronization uses the
 *  fact the read from a pipe end is blocking.
 *
 *  This is the main file which forks 4 processes
 *
 *  1. Turtle:
 *     This process updates the position of the turtle each time it gets to run.
 *     It receives the updated value of struct race from the reporter, updates its
 *     position and writes back to the reporter process its updated struct.
 *  2. Hare:
 *     This process updates the position of the hare each time it gets to run.
 *     It receives the updated value of struct race from the reporter, updates its
 *     position and writes back to the reporter process its updated struct.
 *  3. Reported:
 *     This process prints the current status of the race. This is kind of a parent process
 *     as in it does all the cross communication. For ex: It notifies the position of the turtle
 *     to the hare so that it can sleep etc.
 *  3. God:
 *     This can be intervened by the user to change the position of the hare or the turtle
 *     at any point in time.
 *     How it works:
 *     The god polls the console for input, the user can press the enter key which will block
 *     all other process and the god process can now continue with repositioning, after which this
 *     change will be notified to the hare and turtle process through the reporter.
 *
 *
 *         | --> Reporter
 *         | --> God
 *  Main - | --> Turtle
 *         | --> Hare
 *
 *  Uses four pipes:
 *
 *  a -> all, r -> reporter, t -> turtle, g -> god.
 *
 *  i)  a2r -> any process that wants to reporter writes through this pipe.
 *  ii) a2h -> any process that wants to hare writes through this pipe.
 *  iii) a2t -> any process that wants to turtle writes through this pipe.
 *  iv) a2g -> any process that wants to god writes through this pipe.
 *
 *
 *  The above four pipes can be used to establish 2-way IPC between any two
 *  processes if needed. For ex: To establish a 2-way IPC between hare and god
 *  the a2h can be used to send data from god to hare and a2g can be used to
 *  send data from hare to god. Since there can be many writers for each pipe,
 *  the reads and writes are designed in such a way that each pipe interprets
 *  the right data it has to receive.
 *
 * */
#include "../include/race.h"
#include "../include/standard.h"
#include "../include/params.h"
#include "../include/procs_threads.h"

int main(int argc, char **argv) {
	int status[4];
	memset(pid, 0, sizeof(pid));
	init_race();
	// Create the four pipes
	pipe(a2r);
	pipe(a2g);
	pipe(a2h);
	pipe(a2t);
	/*
	 * Written in this way so that there are exactly 5 processes including the parent.
	 * uses the fact that child gets pid 0 after fork.
	 * */
	pid[GOD] = fork();
	pid[REPORT] = pid[GOD] > 0 ? fork() : 0;
	pid[HARE] = (pid[GOD] > 0 && pid[REPORT] > 0) ? fork() : 0;
	pid[TURTLE] = (pid[GOD] > 0 && pid[REPORT] > 0 && pid[HARE] > 0) ? fork() : 0;
	if(pid[GOD] == -1 || pid[REPORT] == -1 || pid[HARE] == -1 || pid[TURTLE] == -1) {
		printf("Forking failed, exiting\n");
		return 0;
	}
	else if(pid[GOD] && pid[REPORT] && pid[HARE] && pid[TURTLE]) {
		waitpid(pid[GOD], &status[GOD], 0);
		waitpid(pid[REPORT], &status[REPORT], 0);
		waitpid(pid[TURTLE], &status[TURTLE], 0);
		waitpid(pid[HARE], &status[HARE], 0);
	}
	else if(!pid[GOD] && !pid[REPORT] && !pid[HARE] && !pid[TURTLE]) {
		god_proc();
	}
	else if(pid[GOD] && !pid[REPORT] && !pid[HARE] && !pid[TURTLE]) {
		reporter_proc();
	}
	else if(pid[GOD] && pid[REPORT] && !pid[HARE] && !pid[TURTLE]) {
		hare_proc();
	}
	else if (pid[GOD] && pid[REPORT] && pid[HARE] && !pid[TURTLE]) {
		turtle_proc();
	}

	/*
	 * This ensures all the processes close all the ends of their pipes before exiting.
	 * */
	for(int i = 0;i < 2; i++) {
		close(a2g[i]);
		close(a2r[i]);
		close(a2t[i]);
		close(a2h[i]);
		close(a2g[i]);
	}
	return 0;
}

