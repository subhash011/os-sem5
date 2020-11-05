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

int kbhit(void)
{
	struct termios oldt, newt;
	int ch;
	int oldf;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

	ch = getchar();

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);

	if(ch != EOF)
	{
		ungetc(ch, stdin);
		return 1;
	}

	return 0;
}

void take_input(Race **race) {
	char conf , who;
	int newpos;
	printf("Do you want to change the race state ? [Y/n] ");
	conf = getchar();
	getchar();
	if(conf == 'Y' || conf == 'y') {
		while (1) {
			printf("Whose position do you want to change ? Hare [H] or Turtle [T] or Quit [Q]");
			who = getchar();
			if(who == 'H' || who == 'h') {
				printf("Curent position: %d", (*race) -> hare_pos);
				printf("\nEnter new position: ");
				scanf("%d", &newpos);
				(*race) -> hare_pos = newpos;
				break;
			} else if (who == 'T' || who == 't') {
				printf("Curent position: %d", (*race) -> turt_pos);
				printf("\nEnter new position: ");
				scanf("%d", &newpos);
				(*race) -> turt_pos = newpos;
				break;
			} else if (who == 'Q' || who == 'q') {
				getchar();
				return;
			} else {
				printf("Invalid option provided");
			}
		}
	} else {
		return;
	}
	getchar();
	(*race) -> god_intervenes = true;
}