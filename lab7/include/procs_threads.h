#ifndef PROCS_THREADS_H
#define PROCS_THREADS_H

#include "./standard.h"
#include "./race.h"

typedef struct Thread_args Thread_args;

pthread_t tid[4];
pthread_mutex_t race_lock;
pthread_mutex_t cons_lock;

struct Thread_args {
	pthread_mutex_t race_lock;
	pthread_mutex_t cons_lock;
	pthread_cond_t god_wait;
	Race **race;
};

void god_proc();
void hare_proc();
void turtle_proc();
void reporter_proc();

void* god_thread();
void* hare_thread();
void* turtle_thread();
void *reporter_thread();

#endif
