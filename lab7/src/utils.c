#include "../include/race.h"
#include "../include/standard.h"
#include "../include/params.h"

/*
 *  This can be called to initialise the race structure.
 *  The explanations of the variables are in the race.h file.
 * */
void init_race() {
	race = (struct Race*) malloc(sizeof(struct Race));
	race -> hare_speed = HARE_SPEED;
	race -> turt_speed = TURT_SPEED;
	race -> hare_pos = 0;
	race -> turt_pos = 0;
	race -> hare_time = 0;
	race -> turt_time = 0;
	race -> distance = RACE_DIST;
	race -> dist_threshold = MAX_GAP;
	race -> winner = 0;
	race -> hare_slept = false;
	race -> print_interval = PRINT_INTERVAL;
	race -> god_intervened = false;
}
/*
 *  prints the state of the race when called.
 * */
void print_race() {
	printf("Hare pos: %ld, Turtle pos: %ld, Hare speed: %ld, Turtle speed: %ld\n",
	       race -> hare_pos, race -> turt_pos, race -> hare_speed, race -> turt_speed);
}

/*
 *  used to listen for keypress event for the god process.
 * */
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

/*
 *  this function can be called to take input from the god process.
 *  it sets god_intervened to true.
 * */
void take_input() {
	char conf , who;
	long newpos;
	printf("Do you want to change the race state ? [Y/n] ");
	conf = getchar();
	getchar();
	if(conf == 'Y' || conf == 'y') {
		while (1) {
			printf("Whose position do you want to change ? Hare [H] or Turtle [T] or Quit [Q]");
			who = getchar();
			if(who == 'H' || who == 'h') {
				printf("Curent position: %ld", race -> hare_pos);
				printf("\nEnter new position: ");
				scanf("%ld", &newpos);
				race -> hare_pos = newpos;
				break;
			} else if (who == 'T' || who == 't') {
				printf("Curent position: %ld", race -> turt_pos);
				printf("\nEnter new position: ");
				scanf("%ld", &newpos);
				race -> turt_pos = newpos;
				break;
			} else if (who == 'Q' || who == 'q') {
				getchar();
				return;
			} else {
				printf("Invalid option provided\n");
			}
		}
	} else {
		return;
	}
	getchar();
	race -> god_intervened = true;
}