#include "../include/procs_threads.h"
#include "../include/race.h"
#include "../include/params.h"
#include "../include/standard.h"

void *reporter_thread(void *args) {
	Thread_args *targs = (Thread_args *)args;
	Race **race = targs -> race;
	pthread_mutex_t cons_lock = targs -> cons_lock;
	while((*race) -> turt_pos < (*race) -> distance || (*race) -> hare_pos < (*race) -> distance) {
		usleep((*race) -> print_interval);
		pthread_mutex_lock (&cons_lock);
		print_race(*race);
		pthread_mutex_unlock (&cons_lock);
	}
	print_race(*race);
	pthread_exit(NULL);
}

void reporter(Race **race) {
	close(a2h_read);
	close(a2t_read);
	close(a2g_read);
	close(a2r_write);
	(*race) -> hare_pos = 0;
	(*race) -> turt_pos = 0;
	(*race) -> hare_time = 0;
	(*race) -> turt_time = 0;
	print_race(*race);
	usleep((*race) -> print_interval);
	Race *t = (struct Race*) malloc(sizeof(struct Race));
	Race *h = (struct Race*) malloc(sizeof(struct Race));
	Race *g = (struct Race*) malloc(sizeof(struct Race));
	int itr = 0;
	for(;;) {
		write(a2t_write, (*race), sizeof(*race));
		read(a2r_read, t, sizeof(*race));
		write(a2h_write, (*race), sizeof(*race));
		read(a2r_read, h, sizeof(*race));
		if(h -> hare_slept) {
			(*race) -> turt_pos = h -> turt_pos;
			(*race) -> turt_time = h -> turt_time;
		} else {
			(*race) -> turt_pos = t -> turt_pos;
			(*race) -> turt_time = t -> turt_time;
		}
		(*race) -> hare_pos = h -> hare_pos;
		(*race) -> hare_time = h -> hare_time;
		print_race((*race));
		if(turt_completed) {
			(*race) -> winner = TURTLE;
			break;
		} else if(hare_completed) {
			(*race) -> winner = HARE;
			break;
		}
		write(a2g_write, (*race), sizeof(*race));
		read(a2r_read, (*race), sizeof(*race));
		if((*race) -> god_intervened) {
			(*race) -> god_intervened = false;
			print_race((*race));
			usleep((*race) -> print_interval);
		}
	}
	write(a2g_write, (*race), sizeof(*race));
	write(a2h_write, (*race), sizeof(*race));
	write(a2t_write, (*race), sizeof(*race));
	printf("Winner: %s\n", (*race) -> winner == 1 ? "Hare" : "Turtle");
	close(a2h_write);
	close(a2t_write);
	close(a2r_read);
}