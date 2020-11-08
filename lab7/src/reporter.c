#include "../include/procs_threads.h"
#include "../include/race.h"
#include "../include/params.h"
#include "../include/standard.h"

/*
 * reporter function for simulation using processes
 * */
void reporter_proc(void) {
	close(a2h_read);
	close(a2t_read);
	close(a2g_read);
	close(a2r_write);
	start_race();
	print_race();
	usleep(race -> print_interval);
	Race *t = (Race*) malloc(sizeof(Race));
	Race *h = (Race*) malloc(sizeof(Race));
	Race *g = (Race*) malloc(sizeof(Race));
	int itr = 0;
	for(;;) {
		write(a2t_write, race, sizeof(Race));
		read(a2r_read, t, sizeof(Race));
		write(a2h_write, race, sizeof(Race));
		read(a2r_read, h, sizeof(Race));
		if(h -> hare_slept) {
			race -> turt_pos = h -> turt_pos;
			race -> turt_time = h -> turt_time;
		} else {
			race -> turt_pos = t -> turt_pos;
			race -> turt_time = t -> turt_time;
		}
		race -> hare_pos = h -> hare_pos;
		race -> hare_time = h -> hare_time;
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
			print_race();
			usleep(race -> print_interval);
		}
	}
	write(a2g_write, race, sizeof(Race));
	write(a2h_write, race, sizeof(Race));
	write(a2t_write, race, sizeof(Race));
	print_result(false);
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
		pthread_mutex_lock (&cons_lock);
		usleep(race -> print_interval);
		if(race_state_changed) {
			print_race();
		}
		*prev_state = *race;
		pthread_mutex_unlock (&cons_lock);
	}
	print_race();
	print_result(true);
	pthread_exit(NULL);
}