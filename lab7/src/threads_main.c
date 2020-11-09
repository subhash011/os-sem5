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
 *     The god thread polls the console for input, the user can press any key to block all the
 *     other threads since the god process acquires all the locks before getting to run, after this, the
 *     god process can now continue with repositioning.
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

int main() {
	memset(tid, 0, sizeof(tid));
	memset(tid, 0, sizeof(tid));
	init_race();
	race -> distance = 1e8;
	race -> dist_threshold = 1e3;
	race -> print_interval = 0;
	if(pthread_mutex_init(&hare_lock, NULL) != 0) {
		printf("Initializing mutex for hare failed! Exiting.\n");
		return 0;
	}
	if(pthread_mutex_init(&turt_lock, NULL) != 0) {
		printf("Initializing mutex for turtle failed! Exiting.\n");
		return 0;
	}
	if(pthread_mutex_init(&cons_lock, NULL) != 0) {
		printf("Initializing mutex for console failed! Exiting.\n");
		return 0;
	}
	pthread_create (&tid[REPORT], NULL, reporter_thread, NULL);
	usleep(START_DELAY); // let the reporter thread run first so that it can start the race.
	pthread_create (&tid[GOD], NULL, god_thread, NULL);
	pthread_create (&tid[HARE], NULL, hare_thread, NULL);
	pthread_create (&tid[TURTLE], NULL, turtle_thread, NULL);

	pthread_join (tid[REPORT], NULL);
	pthread_join (tid[GOD], NULL);
	pthread_join (tid[HARE], NULL);
	pthread_join (tid[TURTLE], NULL);

	return 0;
}