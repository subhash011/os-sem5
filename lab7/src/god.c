#include "../include/procs_threads.h"
#include "../include/race.h"
#include "../include/params.h"
#include "../include/standard.h"

void god_proc(Race **race) {
	int ch;
	close(a2g_write);
	close(a2r_read);
	int c;
	for(;;) {
		read(a2g_read, (*race), sizeof(Race));
		if((*race) -> winner != 0) break;
		usleep((*race) -> print_interval);
		// if user has pressed a key, consider repositioning
		if(kbhit()) {
			getchar();
			getchar();
			take_input(race);
		} else {
			(*race) -> god_intervened = false;
		}
		write(a2r_write, (*race), sizeof(Race));
	}
	close(a2g_read);
	close(a2r_write);
}

void *god_thread(void *args) {
	Thread_args *targs = (Thread_args *) args;
	Race **race = targs -> race;
	pthread_mutex_t cons_lock = targs -> cons_lock;
	pthread_mutex_t race_lock = targs -> race_lock;
	while((*race) -> turt_pos < (*race) -> distance || (*race) -> hare_pos < (*race) -> distance) {
		usleep((*race) -> print_interval);
		pthread_mutex_lock (&cons_lock);
		pthread_mutex_lock (&race_lock);
		if(kbhit()) {
			getchar();
			getchar();
			take_input(race);
		}
		pthread_mutex_unlock (&cons_lock);
		pthread_mutex_unlock (&race_lock);
		pthread_mutex_unlock (&race_lock);

	}
	pthread_exit(NULL);
}