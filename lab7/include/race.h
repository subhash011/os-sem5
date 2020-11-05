#ifndef RACE_H
#define RACE_H

#include <stdbool.h>
#include <semaphore.h>
#include <pthread.h>

typedef struct Race Race;
typedef struct Mutex Mutex;
typedef struct Semaphores Semaphores;

struct Race {
	int hare_pos;
	int turt_pos;
	int hare_speed;
	int turt_speed;
	int distance;
	int dist_threshold;
	bool hare_slept;
	int winner;
	int print_interval;
	bool god_intervenes;
};

struct Mutex {
	pthread_mutex_t lock;
	pthread_cond_t r2h;
	pthread_cond_t r2t;
	int turn;
};

enum ProcessMap {
	GOD,
	HARE,
	TURTLE,
	REPORT,
};

struct Semaphores {
	sem_t *h2r;
	sem_t *t2r;
	sem_t *r2h;
	sem_t *r2t;
	sem_t *g2r;
	sem_t *r2g;
};

void print_race(Race*);

void init_race(Race**);

void init_mutex(Mutex**);

int kbhit(void);

void take_input(Race **race);

#endif
