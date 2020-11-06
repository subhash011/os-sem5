#ifndef PROCS_THREADS_H
#define PROCS_THREADS_H

#include "./standard.h"
#include "./race.h"

typedef struct Thread_args Thread_args;

struct Thread_args {
	pthread_mutex_t race_lock;
	pthread_mutex_t cons_lock;
	Race **race;
};


void god_proc(Race **race);
void hare_proc(Race **race);
void turtle_proc(Race **race);
void reporter_proc(Race **race);

void* god_thread(void*);
void* hare_thread(void*);
void* turtle_thread(void*);
void *reporter_thread(void*);

#endif
