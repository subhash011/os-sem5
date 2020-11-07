#include "../include/procs_threads.h"
#include "../include/race.h"
#include "../include/params.h"
#include "../include/standard.h"

/*
 * god function for simulation using processes
 * */
void god_proc() {
	int ch;
	close(a2g_write);
	close(a2r_read);
	int c;
	for(;;) {
		read(a2g_read, race, sizeof(Race));
		if(race -> winner != 0) break;
		usleep(race -> print_interval);
		// if user has pressed a key, consider repositioning
		if(kbhit()) {
			take_input(&race);
		} else {
			race -> god_intervened = false;
		}
		write(a2r_write, race, sizeof(Race));
	}
	close(a2g_read);
	close(a2r_write);
}

/*
 * god function for simulation using threads
 * */
void *god_thread() {
	while(!hare_completed || !turt_completed) {
		pthread_mutex_lock (&cons_lock);
		pthread_mutex_lock (&race_lock);
		if(kbhit()) {
			take_input(&race);
		}
		pthread_mutex_unlock (&race_lock);
		pthread_mutex_unlock (&cons_lock);

	}
	pthread_exit(NULL);
}