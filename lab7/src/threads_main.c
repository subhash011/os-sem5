#include "../include/race.h"
#include "../include/standard.h"
#include "../include/params.h"
#include "../include/procs_threads.h"


pthread_t tid[4];
pthread_mutex_t race_lock;
pthread_mutex_t cons_lock;

Race *race;

//void *reporter();
void *god();
void *hare();
void *turtle();

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

	pthread_create (&tid[TURTLE], NULL, turtle, NULL);
	pthread_create (&tid[HARE], NULL, hare, NULL);
	pthread_create (&tid[REPORT], NULL, reporter_thread, (void *) args);
	pthread_create (&tid[GOD], NULL, god, NULL);

	pthread_join (tid[TURTLE], NULL);
	pthread_join (tid[HARE], NULL);
	pthread_join (tid[REPORT], NULL);
	pthread_join (tid[GOD], NULL);

	printf("Hare's stats: (%ld in %ld)\nTurtle's stats: (%ld in %ld)\n", race -> hare_pos, race -> hare_time, race -> turt_pos, race -> turt_time);

	if (turt_won) {
		printf("Winner: Turtle");
	} else if (hare_won) {
		printf("Winner: Hare");
	} else {
		printf("Race Tied");
	}
	return 0;
}

//void *reporter() {
//
//	while(race -> turt_pos < race -> distance || race -> hare_pos < race -> distance) {
//		usleep(race -> print_interval);
//		pthread_mutex_lock (&cons_lock);
//		print_race(race);
//		pthread_mutex_unlock (&cons_lock);
//	}
//	print_race(race);
//	pthread_exit(NULL);
//}

void *god() {
	while(race -> turt_pos < race -> distance || race -> hare_pos < race -> distance) {
		pthread_mutex_lock (&cons_lock);
		pthread_mutex_lock (&race_lock);
		usleep(race -> print_interval);
		if(kbhit()) {
			getchar();
			getchar();
			take_input(&race);
		}
		pthread_mutex_unlock (&cons_lock);
		pthread_mutex_unlock (&race_lock);
		pthread_mutex_unlock (&race_lock);

	}
	pthread_exit(NULL);
}

void *hare() {
	srand(time(0));
	while(race -> hare_pos < race -> distance) {
		if(hare_should_sleep) {
			int sleeptime = rand() % (race -> distance);
			usleep(sleeptime);
			race -> hare_time += sleeptime;
		}
		pthread_mutex_lock (&race_lock);
		race -> hare_pos += race -> hare_speed;
		race -> hare_time++;
		pthread_mutex_unlock (&race_lock);
	}
	pthread_exit(NULL);
}

void *turtle() {

	while(race -> turt_pos < race -> distance) {
		pthread_mutex_lock (&race_lock);
		race -> turt_pos += race -> turt_speed;
		race -> turt_time++;
		pthread_mutex_unlock (&race_lock);
	}
	pthread_exit(NULL);
}