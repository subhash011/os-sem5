#ifndef RACE_H
#define RACE_H

#include <stdbool.h>
#include <semaphore.h>
#include <pthread.h>

typedef struct Race Race;
typedef struct Mutex Mutex;
typedef struct Semaphores Semaphores;

int a2r[2], a2h[2], a2t[2], a2g[2];
pid_t pid[4];

struct Race {
	long hare_pos; // stores the hare position at any given point.
	long turt_pos; // stores the turtle position at any given point.
	long hare_time; // time (unit time = print_interval) taken by hare to complete race.
	long hare_speed; // stores the hare speed, this can changed while initialising Race struct.
	long turt_time;  // time (unit time = print_interval) taken by turtle to complete race.
	long turt_speed; // stores the turtle speed, this can changed while initialising Race struct.
	long distance; // stores the total distance of the race
	long dist_threshold; // stores the min distance b/w hare and turtle for the hare to go to sleep.
	bool hare_slept; // reports if the hare slept or not to the reporter process
	int winner; // stores the winner of the race
	long print_interval; // this represents a unit time in program.
	bool god_intervened; // tells the reporter process if the god has intervened.
};

enum ProcessMap {
	GOD,
	HARE,
	TURTLE,
	REPORT,
};

void print_race(Race*);

void init_race(Race**);

int kbhit(void);

void take_input(Race **race);

#endif
