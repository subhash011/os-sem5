/*
 *  Race *race:
 *  This struct defines the state of the race, it contains various parameters
 *  which are explained in the race.h file
 *
 *  There are 2 mutexes used race_lock and cons_lock, race_lock is acquired when a thread has to
 *  update the race structure while the cons_lock is acquired when a thread wants to perform operations
 *  on the console.
 *
 *  This is the main file which creates the following 4 threads
 *  Since the threads use a global race structure, no communication methods are established
 *
 *  1. Turtle:
 *     This process updates the position of the turtle each time it gets to run.
 *  2. Hare:
 *     This process updates the position of the hare each time it gets to run.
 *  3. Reported:
 *     This process prints the current status of the race only if it was not equal to the
 *     previous state. This check is important here because there is no fixed time as to when
 *     the reporter process gets to run whereas in the process version since pipe reads are blocked we
 *     can be sure that the state changes during each call to print_race.
 *  3. God:
 *     This can be intervened by the user to change the position of the hare or the turtle
 *     at any point in time.
 *     How it works:
 *     The god thread polls the console for input, the user can press any character and hit enter or
 *     more easily hit the enter key twice, this will block all other threads since the god process
 *     acquires all the locks before getting to run, after this, the god process can now continue with
 *     repositioning.
 *
 *
 *         | --> Reporter
 *         | --> God
 *  Main - | --> Turtle
 *         | --> Hare
 *
 *
 * */


#include "../include/race.h"
#include "../include/standard.h"
#include "../include/params.h"
#include "../include/procs_threads.h"

pthread_t tid[4];
pthread_mutex_t race_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t cons_lock = PTHREAD_MUTEX_INITIALIZER;
//pthread_cond_t god_wait = PTHREAD_COND_INITIALIZER;

Race *race;

int main() {
	// initialise tid's to zero
	memset(tid, 0, sizeof(tid));
	init_race(&race);
	race -> distance = 1e8;
	race -> dist_threshold = 1e2;
	race -> print_interval = 1e2;
	/*
	 * Fill the thread ars struct so that the values can be passed on to threads.
	 * */
	Thread_args *args = (Thread_args*) malloc (sizeof(Thread_args));
	args -> cons_lock = cons_lock;
	args -> race_lock = race_lock;
	args -> race = &race;

	pthread_create (&tid[TURTLE], NULL, turtle_thread, (void *) args);
	pthread_create (&tid[HARE], NULL, hare_thread, (void *) args);
	pthread_create (&tid[REPORT], NULL, reporter_thread, (void *) args);
	pthread_create (&tid[GOD], NULL, god_thread, (void *) args);

	pthread_join (tid[TURTLE], NULL);
	pthread_join (tid[HARE], NULL);
	pthread_join (tid[REPORT], NULL);
	pthread_join (tid[GOD], NULL);

	printf("Hare's stats: (%ld in %ld)\nTurtle's stats: (%ld in %ld)\n",
		race -> hare_pos, race -> hare_time, race -> turt_pos, race -> turt_time);

	if (turt_won) {
		printf("Winner: Turtle");
	} else if (hare_won) {
		printf("Winner: Hare");
	} else {
		printf("Race Tied");
	}
	return 0;
}