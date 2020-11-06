#include "../include/procs_threads.h"
#include "../include/race.h"
#include "../include/params.h"
#include "../include/standard.h"

/*
 * turtle function for simulation using processes
 * */
void turtle_proc(Race **race) {
	close(a2t_write);
	close(a2r_read);
	for(;;) {
		read(a2t_read, (*race), sizeof(Race));
		if((*race) -> winner != 0) break;
		(*race) -> turt_pos += (*race) -> turt_speed;
		(*race) -> turt_time++;
		write(a2r_write, (*race), sizeof(Race));
	}
	close(a2t_read);
	close(a2r_write);
}

/*
 * turtle function for simulation using threads
 * */
void *turtle_thread(void *args) {
	Thread_args *targs = (Thread_args *) args;
	Race **race = targs -> race;
	pthread_mutex_t race_lock = targs -> race_lock;
	while((*race) -> turt_pos < (*race) -> distance) {
		pthread_mutex_lock (&race_lock);
		(*race) -> turt_pos += (*race) -> turt_speed;
		(*race) -> turt_time++;
		pthread_mutex_unlock (&race_lock);
	}
	pthread_exit(NULL);
}