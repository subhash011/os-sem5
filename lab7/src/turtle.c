#include "../include/procs_threads.h"
#include "../include/race.h"
#include "../include/params.h"
#include "../include/standard.h"

/*
 * turtle function for simulation using processes
 * */
void turtle_proc(void) {
	close(a2t_write);
	close(a2r_read);
	for(;;) {
		read(a2t_read, race, sizeof(Race));
		if(race -> winner != 0) break;
		race -> turt_pos += race -> turt_speed;
		race -> turt_time++;
		write(a2r_write, race, sizeof(Race));
	}
	close(a2t_read);
	close(a2r_write);
}

/*
 * turtle function for simulation using threads
 * */
void *turtle_thread(void* args) {
	while(!turt_completed) {
		pthread_mutex_lock (&turt_lock);
		race -> turt_pos += race -> turt_speed;
		race -> turt_time++;
		pthread_mutex_unlock (&turt_lock);
	}
	pthread_exit(NULL);
}