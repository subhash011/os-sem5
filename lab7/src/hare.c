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
	int multiplier;
	for(;;) {
		read(a2h_read, race, sizeof(Race));
		if(race -> winner != 0) break;
		// if hare is far ahead in the race, let it sleep
		// since sleep is blocking, here the counter was
		// stopped from incrementing until hare sleeps the
		// random amount of time or the god wakes up
		// the hare.
		if(race -> hare_slept) {
			if(multiplier > 0) {
				multiplier--;
			} else {
				race -> hare_slept = false;
				race -> hare_pos += race -> hare_speed;
			}
		} else if(hare_should_sleep) {
			race -> hare_slept = true;
			multiplier = (rand() % (2* race -> dist_threshold/race -> turt_speed));
		} else {
			race -> hare_pos += race -> hare_speed;
		}
		race -> hare_time++;
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
	struct timespec wait_time;
	struct timeval now;
	long prev_turt_pos;
	while(!hare_completed) {
		/*
		 * sleep within the lock is unavoidable since pthread_con_timedwait
		 * needs a lock to be held, and this is a clean way for the god to
		 * wake up the hare if it's sleeping.
		 * */
		pthread_mutex_lock (&hare_lock);
		if(hare_should_sleep) {
			prev_turt_pos = race -> turt_pos;
			long sleeptime = ((rand() % 500000) + 1) * (race -> print_interval == 0 ? 1 : race -> print_interval);
			gettimeofday(&now, NULL);
			wait_time.tv_sec = now.tv_sec;
			wait_time.tv_nsec = (now.tv_usec + sleeptime) * 1000;
			race -> hare_slept = true;
			pthread_cond_timedwait(&hare_wakeup, &hare_lock, &wait_time);
			race -> hare_slept = false;
			// time in the simulated world is not the same as real world
			// hence this calculation to update the hare time.
			race -> hare_time += (race -> turt_pos - prev_turt_pos) / race -> turt_speed;
		}
		race -> hare_pos += race -> hare_speed;
		race -> hare_time++;
		pthread_mutex_unlock (&hare_lock);
	}
	pthread_exit(NULL);
}