#include "../include/procs_threads.h"
#include "../include/race.h"
#include "../include/params.h"
#include "../include/standard.h"

void handle_sleep(int signum) {
	race -> hare_slept = true;
}

void handle_wakeup(int signum) {
	race -> hare_slept = false;
}

/*
 * reporter function for simulation using processes
 * */
void reporter_proc(void) {
	close(a2h_read);
	close(a2t_read);
	close(a2g_read);
	close(a2r_write);
	start_race();
	long remsleep = START_DELAY - race -> print_interval;
	if(remsleep > 0) usleep(remsleep);
	print_race();
	usleep(race -> print_interval);
	Race *t = (Race*) malloc(sizeof(Race));
	Race *h = (Race*) malloc(sizeof(Race));
	Race *g = (Race*) malloc(sizeof(Race));
	signal(SIGUSR1, handle_sleep);
	signal(SIGUSR2, handle_wakeup);
	int itr = 0;
	for(;;) {
		write(a2t_write, race, sizeof(Race));
		read(a2r_read, t, sizeof(Race));
		race -> turt_pos = t -> turt_pos;
		race -> turt_time = t -> turt_time;
		write(a2h_write, race, sizeof(Race));
		read(a2r_read, h, sizeof(Race));
		race -> god_woke_hare = h -> god_woke_hare;
		race -> hare_pos = h -> hare_pos;
		race -> hare_time = h -> hare_time;
		race -> hare_slept = h -> hare_slept;
		print_race();
		if(turt_completed) {
			race -> winner = TURTLE;
			break;
		} else if(hare_completed) {
			race -> winner = HARE;
			break;
		}
		write(a2g_write, race, sizeof(Race));
		read(a2r_read, race, sizeof(Race));
		if(race -> god_intervened) {
			race -> god_intervened = false;
			if(turt_completed) {
				race -> winner = TURTLE;
			} else if(hare_completed) {
				race -> winner = HARE;
			}
			print_race();
			usleep(race -> print_interval);
		}
	}
	write(a2g_write, race, sizeof(Race));
	write(a2h_write, race, sizeof(Race));
	write(a2t_write, race, sizeof(Race));
	if(race -> hare_pos >= race -> distance && race -> turt_pos >= race -> distance )
		race -> winner = 0;
	print_result();
	close(a2h_write);
	close(a2t_write);
	close(a2r_read);
}

/*
 * reporter function for simulation using threads
 * */
void *reporter_thread(void* args) {
	Race *prev_state = (Race *) malloc(sizeof(Race));
	start_race();
	while(!hare_completed || !turt_completed) {
		usleep(race -> print_interval);
		pthread_mutex_lock (&cons_lock);
		if(race_state_changed) {
			print_race();
		}
		*prev_state = *race;
		pthread_mutex_unlock (&cons_lock);
	}
	print_race();
	/*
	 * lock not needed to update race here because
	 * all other threads would have exited by now.
	 * */
	if(hare_won) {
		race -> winner = HARE;
	} else if (turt_won) {
		race -> winner = TURTLE;
	} else {
		race -> winner = 0;
	}
	print_result();
	pthread_exit(NULL);
}