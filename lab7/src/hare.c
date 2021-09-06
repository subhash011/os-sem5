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
	long sleeptime;
	for(;;) {
		read(a2h_read, race, sizeof(Race));
		if(race -> winner != 0) break;
		// if hare is far ahead in the race, let it sleep
		// since sleep is blocking, here the counter was
		// stopped from incrementing until hare sleeps the
		// random amount of time or the god wakes up
		// the hare.
		if(race -> hare_slept) {
			if(sleeptime > 0) {
				sleeptime--;
			} else {
				race -> hare_slept = false;
				race -> hare_pos += race -> hare_speed;
			}
		} else if(hare_should_sleep && (!race -> god_woke_hare)) {
			race -> hare_slept = true;
			// this gives a random chance for the turtle to overtake the hare.
			sleeptime = (rand() % turt_catch_up) + turt_catch_up;
			printf("============================================\n");
		    printf("Hare will sleep till turtle reaches %ld\n", race -> turt_pos + (sleeptime * race-> turt_speed));
		    printf("============================================\n");
		} else {
			race -> god_woke_hare = false;
			race -> hare_pos += race -> hare_speed;
		}
		race -> hare_time++;
		write(a2r_write, race, sizeof(Race));
	}
	write(a2r_write, race, sizeof(Race));
	close(a2h_read);
	close(a2r_write);
}

/*
 * hare function for simulation using threads
 * */
void *hare_thread(void* args) {
	srand(time(0));
	long prev_turt_pos, sleeptime;
	struct timespec wait_time;
	struct timeval now;
	while(!hare_completed) {
		usleep(race -> print_interval);
		/*
		 * sleep within the lock is unavoidable since pthread_con_timedwait
		 * needs a lock to be held, and this is a clean way for the god to
		 * wake up the hare if it's sleeping.
		 * */
		pthread_mutex_lock (&hare_lock);
		if(hare_should_sleep) {
			prev_turt_pos = race -> turt_pos;
			sleeptime = (rand() % turt_catch_up) + turt_catch_up;
			sleeptime *= race -> print_interval;
			sleeptime /= (long)1e6;
			gettimeofday(&now, NULL);
			wait_time.tv_sec = now.tv_sec + sleeptime;
			wait_time.tv_nsec = now.tv_usec * 1000;
			race -> hare_slept = true;
			printf("================================================\n");
			long dist_covered = sleeptime * ((long)(1e6/race -> print_interval)) * race -> turt_speed;
			dist_covered += race -> turt_pos;
			printf("Hare will sleep till turtle is between %ld and %ld\n", dist_covered - 1, dist_covered + 1);
			printf("================================================\n");
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