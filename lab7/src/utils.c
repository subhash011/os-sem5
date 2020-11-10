#include "../include/race.h"
#include "../include/standard.h"
#include "../include/params.h"
#include "../include/procs_threads.h"

/*
 *  This can be called to initialise the race structure.
 *  The explanations of the variables are in the race.h file.
 * */
void init_race(void) {
	race = (struct Race*) malloc(sizeof(struct Race));
	race -> hare_speed = HARE_SPEED;
	race -> turt_speed = TURT_SPEED;
	race -> distance = RACE_DIST;
	race -> dist_threshold = MAX_GAP;
	race -> hare_slept = false;
	race -> print_interval = PRINT_INTERVAL;
	race -> god_intervened = false;
}

/*
 * This function is called by the reporter to start the race.
 * */
void start_race(void) {
	race -> hare_pos = 0;
	race -> turt_pos = 0;
	race -> hare_time = 0;
	race -> turt_time = 0;
	race -> winner = 0;
	printf("=============== Race Starts ===============\n");
	printf("Race Distance: %ld\n", race -> distance);
	printf("Hare Speed: %ld\n", race -> hare_speed);
	printf("Turtle Speed: %ld\n", race -> turt_speed);
	printf("Race will start in %ld seconds\n", (long)(START_DELAY/1e6));
	printf("===========================================\n\n");
	usleep(race -> print_interval);
}

void print_result(void) {
	printf("\n=============== Race Ends ===============\n");
	printf("Hare's stats: (%ld in %ld)\nTurtle's stats: (%ld in %ld)\n", race -> hare_pos, race -> hare_time, race -> turt_pos, race -> turt_time);
	char *winner = race -> winner == HARE ? "Hare" : "Turtle";
	if(race -> winner == 0) {
		printf("Race Tied.\n");
	} else {
		printf("Winner: %s\n", winner);
	}
	printf("==========================================\n");
}

/*
 *  prints the state of the race when called.
 * */
void print_race(void) {
	printf("Hare pos: (%ld / %ld), Turtle pos: (%ld / %ld)\n",
	       race -> hare_pos, race -> distance, race -> turt_pos, race -> distance);
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


void wake_hare_proc() {
	char to_wake;
	while(1) {
		printf("Hare is sleeping, do you want to wake the hare up ? [Y/n] ");
		to_wake = getchar();
		if(to_wake == 'y' || to_wake == 'Y') {
			race -> hare_slept = false;
			getchar();
			break;
		} else if (to_wake == 'n' || to_wake == 'N') {
			getchar();
			break;
		} else {
			if(to_wake == '\n') {
				printf("Invalid option, select [Y] or [N]\n");
				ungetc('\n', stdin);
			} else {
				printf("[%c] is an invalid option, select [Y] or [N]\n", to_wake);
			}
		}
		getchar();
	}
}

void wake_hare_thread() {
	char to_wake;
	while(1) {
		printf("Hare is sleeping, do you want to wake the hare up ? [Y/n] ");
		to_wake = getchar();
		if(to_wake == 'y' || to_wake == 'Y') {
			pthread_cond_signal(&hare_wakeup);
			getchar();
			break;
		} else if (to_wake == 'n' || to_wake == 'N') {
			getchar();
			break;
		} else {
			if(to_wake == '\n') {
				printf("Invalid option, select [Y] or [N]\n");
				ungetc('\n', stdin);
			} else {
				printf("[%c] is an invalid option, select [Y] or [N]\n", to_wake);
			}
		}
		getchar();
	}
}

/*
 *  this function can be called to take input from the god process.
 *  it sets god_intervened to true.
 * */
void take_input(bool is_thread) {
	char conf , who, to_wake;
	long newpos;
	if(getchar() != '\n') {
		printf("\n");
	}
	while(1) {
		if(race -> hare_slept) {
			if(is_thread) {
				wake_hare_thread();
			}  else {
				wake_hare_proc();
			}
		}
		printf("Do you want to change the race state ? [Y/n] ");
		conf = getchar();
		if(conf == 'Y' || conf == 'y') {
			getchar();
			while (1) {
				printf("Whose position do you want to change ? Hare [H] or Turtle [T] or Quit [Q] ");
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
					break;
				} else {
					if(who == '\n') {
						printf("Invalid option, select [H] or [T] or [Q]\n");
						ungetc('\n', stdin);
					} else {
						printf("[%c] is an invalid option, select [H] or [T] or [Q]\n", who);
					}
					getchar();
				}
			}
			break;
		} else if (conf == 'N' || conf == 'n') {
			break;
		} else {
			if(conf == '\n') {
				printf("Invalid option, select [Y] or [N]\n");
				ungetc('\n', stdin);
			} else {
				printf("[%c] is an invalid option, select [Y] or [N]\n", conf);
			}
			getchar();
		}
	}
	getchar();
	race -> god_intervened = true;
}