#include "../include/race.h"
#include "../include/tolink.h"
#include "../include/standard.h"
#include "../include/params.h"


Race *race;
Mutex *mutex;
pthread_t tid[4];
int retval[4];


void* god();
void* reporter();
void* hare();
void* turtle();

int main(int argc, char **argv) {
	init_race(&race);
	init_mutex(&mutex);
	if (pthread_mutex_init(&mutex -> lock, NULL) != 0) {
		printf("Mutex init has failed.\n");
		exit(1);
	}
//	if (pthread_cond_init(&mutex -> r2t, NULL) != 0 || pthread_cond_init(&mutex -> r2h, NULL) != 0) {
//		printf("Condition init failed.\n");
//		exit(1);
//	}
//	retval[GOD] = pthread_create(&tid[GOD], NULL, god, NULL);
	retval[REPORT] = pthread_create(&tid[REPORT], NULL, reporter, NULL);
	retval[HARE] = pthread_create(&tid[HARE], NULL, hare, NULL);
	retval[TURTLE] = pthread_create(&tid[TURTLE], NULL, turtle, NULL);
	if(retval[GOD] || retval[REPORT] || retval[HARE] || retval[TURTLE]) {
		printf("Thread creation failed");
		exit(1);
	}
	pthread_mutex_destroy(&mutex->lock);
	pthread_exit(NULL);
}

void* god() {
	pthread_detach(tid[GOD]);
//	for(;;) {
//		pthread_mutex_lock(&mutex -> lock);
//		if (!race -> winner) break;
//		pthread_mutex_unlock(&mutex -> lock);
//	}
	pthread_exit(NULL);
}

void* reporter() {
	pthread_detach(tid[REPORT]);
	for(;;) {
		pthread_mutex_lock(&mutex -> lock);
		if (race -> winner != 0) break;
		print_race(race);
		if(race -> turt_pos >= race -> distance) {
			race -> winner = TURTLE;
			break;
		} else if (race -> hare_pos >= race -> distance) {
			race -> winner = HARE;
			break;
		}
		pthread_mutex_unlock(&mutex -> lock);
	}
	printf("Winner: %s\n", race -> winner == 1 ? "Hare" : "Turtle");
	pthread_exit(NULL);
}

void* hare() {
	pthread_detach(tid[HARE]);
	for(;;) {
		pthread_mutex_lock(&mutex -> lock);
		if (race -> winner != 0) break;
		if(race -> hare_pos - race -> turt_pos >= race -> dist_threshold) {
			race -> hare_slept = true;
			int multiplier = rand() % race -> hare_speed;
			race -> turt_pos += race -> turt_speed * multiplier;
		} else {
			race -> hare_pos += race -> hare_speed;
		}
		pthread_mutex_unlock(&mutex -> lock);
	}
	pthread_exit(NULL);
}

void* turtle() {
	pthread_detach(tid[TURTLE]);
	for(;;) {
		pthread_mutex_lock(&mutex -> lock);
		if (race -> winner != 0) break;
		race -> turt_pos += race -> turt_speed;
		pthread_mutex_unlock(&mutex -> lock);
	}
	pthread_exit(NULL);
}