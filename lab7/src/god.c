#include "../include/procs_threads.h"
#include "../include/race.h"
#include "../include/params.h"
#include "../include/standard.h"

/*
 * god function for simulation using processes
 * */
void god_proc(void) {
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
			take_input(false);
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
void *god_thread(void* args) {
	while(!hare_completed || !turt_completed) {
		pthread_mutex_lock (&cons_lock);
		pthread_mutex_lock (&hare_lock);
		pthread_mutex_lock (&turt_lock);
		if(kbhit()) {
			if(!hare_completed || !turt_completed) {
				take_input(true);
			}
		}
		pthread_mutex_unlock (&turt_lock);
		pthread_mutex_unlock (&hare_lock);
		pthread_mutex_unlock (&cons_lock);
	}
	pthread_exit(NULL);
}