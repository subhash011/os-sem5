#include "../include/procs_threads.h"
#include "../include/race.h"
#include "../include/params.h"
#include "../include/standard.h"

/*
 * hare function for simulation using processes
 * */
void hare_proc(void) {
	close(a2h_write);
	close(a2r_read);
	srand(time(0));
	for(;;) {
		read(a2h_read, race, sizeof(Race));
		if(race -> winner != 0) break;
		// if hare is far ahead in the race, let it sleep
		if(hare_should_sleep) {
			race -> hare_slept = true;
			int multiplier = rand() % (2* race -> dist_threshold/race -> turt_speed);
			race -> turt_pos += race -> turt_speed * multiplier;
			race -> turt_time += multiplier;
			race -> hare_time += multiplier;
		} else {
			race -> hare_pos += race -> hare_speed;
			race -> hare_time++;
		}
		write(a2r_write, race, sizeof(Race));
	}
	close(a2h_read);
	close(a2r_write);
}

/*
 * hare function for simulation using threads
 * */
void *hare_thread(void* args) {
	srand(time(0));
	while(!hare_completed) {
		if(hare_should_sleep) {
			int sleeptime = ((rand() % 3) + 1) * (race -> print_interval == 0 ? 1 : race -> print_interval);
			usleep(sleeptime);
			race -> hare_time += sleeptime;
		}
		pthread_mutex_lock (&hare_lock);
		race -> hare_pos += race -> hare_speed;
		race -> hare_time++;
		pthread_mutex_unlock (&hare_lock);
	}
	pthread_exit(NULL);
}