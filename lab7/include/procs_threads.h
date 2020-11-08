#ifndef PROCS_THREADS_H
#define PROCS_THREADS_H

#include "./standard.h"
#include "./race.h"

pthread_t tid[4];
pthread_mutex_t hare_lock;
pthread_mutex_t turt_lock;
pthread_mutex_t cons_lock;

void god_proc(void);
void hare_proc(void);
void turtle_proc(void);
void reporter_proc(void);

void* god_thread(void*);
void* hare_thread(void*);
void* turtle_thread(void*);
void *reporter_thread(void*);

#endif
