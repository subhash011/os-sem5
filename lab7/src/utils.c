#include "../include/race.h"
#include "../include/standard.h"

void init_race(Race **r) {
	(*r) = (struct Race*) malloc(sizeof(struct Race));
	(*r) -> hare_speed = 50;
	(*r) -> turt_speed = 10;
	(*r) -> distance = 1000;
	(*r) -> dist_threshold = 100;
	(*r) -> winner = 0;
	(*r) -> hare_slept = false;
	(*r) -> print_interval = 2;
	(*r) -> god_intervenes = false;
}

void init_mutex(Mutex **m) {
	(*m) = (struct Mutex*) malloc(sizeof(struct Mutex));
	(*m) -> turn = HARE;

}

void print_race(Race* r) {
	printf("Hare pos: %d, Turtle pos: %d, Hare speed: %d, Turtle speed: %d\n",
	       r -> hare_pos, r->turt_pos, r->	hare_speed, r->turt_speed);
}