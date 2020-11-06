#include "../include/race.h"
#include "../include/standard.h"
#include "../include/params.h"
#include "../include/procs_threads.h"


pthread_t tid[4];
pthread_mutex_t race_lock;
pthread_mutex_t cons_lock;

Race *race;

int main() {
	memset(tid, 0, sizeof(tid));
	init_race(&race);
	if(pthread_mutex_init(&race_lock, NULL) != 0) {
		printf("Initializing mutex for race structure failed! Exiting.\n");
		return 0;
	}
	if(pthread_mutex_init(&cons_lock, NULL) != 0) {
		printf("Initializing mutex for console failed! Exiting.\n");
		return 0;
	}

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