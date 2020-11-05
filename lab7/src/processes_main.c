#include "../include/race.h"
#include "../include/tolink.h"
#include "../include/standard.h"
#include "../include/params.h"

int a2r[2], a2h[2], a2t[2], a2g[2];
pid_t pid[4] = {0, 0, 0, 0};

Race* race;
Semaphores sema;
void hare();
void turtle();
void god();
void reporter();

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

int main(int argc, char **argv) {
	int status[4];
	pipe(a2r);
	pipe(a2g);
	pipe(a2h);
	pipe(a2t);
	sema.g2r = sem_open("/g2r", O_CREAT|O_RDWR, 0644, 0);
	sema.r2g = sem_open("/r2g", O_CREAT|O_RDWR, 0644, 0);
	pid[GOD] = fork();
	pid[REPORT] = pid[GOD] > 0 ? fork() : 0;
	pid[HARE] = (pid[GOD] > 0 && pid[REPORT] > 0) ? fork() : 0;
	pid[TURTLE] = (pid[GOD] > 0 && pid[REPORT] > 0 && pid[HARE] > 0) ? fork() : 0;
	init_race(&race);
	if(pid[GOD] == -1 || pid[REPORT] == -1 || pid[HARE] == -1 || pid[TURTLE] == -1) {
		printf("Forking failed, exiting\n");
		return 0;
	}
	else if(pid[GOD] && pid[REPORT] && pid[HARE] && pid[TURTLE]) {
		waitpid(pid[GOD], &status[GOD], 0);
		waitpid(pid[REPORT], &status[REPORT], 0);
		waitpid(pid[TURTLE], &status[TURTLE], 0);
		waitpid(pid[HARE], &status[HARE], 0);
	}
	else if(!pid[GOD] && !pid[REPORT] && !pid[HARE] && !pid[TURTLE]) {
		god();
	}
	else if(pid[GOD] && !pid[REPORT] && !pid[HARE] && !pid[TURTLE]) {
		reporter();
	}
	else if(pid[GOD] && pid[REPORT] && !pid[HARE] && !pid[TURTLE]) {
		hare();
	}
	else if (pid[GOD] && pid[REPORT] && pid[HARE] && !pid[TURTLE]) {
		turtle();
	}
	for(int i = 0;i < 2; i++) {
		close(a2g[i]);
		close(a2r[i]);
		close(a2t[i]);
		close(a2h[i]);
		close(a2g[i]);
	}
	sem_unlink("/r2g");
	sem_unlink("/g2r");
	return 0;
}

void hare() {
	close(a2h_write);
	close(a2r_read);
	srand(time(0));
	for(;;) {
		read(a2h_read, race, sizeof(*race));
		if(race -> winner != 0) break;
		if(race -> hare_pos - race -> turt_pos >= race -> dist_threshold) {
			race -> hare_slept = true;
			int multiplier = rand() % race -> hare_speed;
			race -> turt_pos += race -> turt_speed * multiplier;
			write(a2r_write, race, sizeof(*race));
		} else {
			race -> hare_pos += race -> hare_speed;
			write(a2r_write, race, sizeof(*race));
		}
	}
	close(a2h_read);
	close(a2r_write);
}

void turtle() {
	close(a2t_write);
	close(a2r_read);
	for(;;) {
		read(a2t_read, race, sizeof(*race));
		if(race -> winner != 0) break;
		race -> turt_pos += race -> turt_speed;
		write(a2r_write, race, sizeof(*race));
	}
	close(a2t_read);
	close(a2r_write);
}

void take_input() {
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
				printf("Curent position: %d", race -> hare_pos);
				printf("\nEnter new position: ");
				scanf("%d", &newpos);
				race -> hare_pos = newpos;
				break;
			} else if (who == 'T' || who == 't') {
				printf("Curent position: %d", race -> turt_pos);
				printf("\nEnter new position: ");
				scanf("%d", &newpos);
				race -> turt_pos = newpos;
				break;
			} else if (who == 'Q' || who == 'q') {
				break;
			} else {
				printf("Invalid option provided");
			}
		}
	} else {
		write(a2r_write, race, sizeof(*race));
		sem_post(sema.g2r);
		return;
	}
	getchar();
	race -> god_intervenes = true;
	write(a2r_write, race, sizeof(*race));
	sem_post(sema.g2r);
}

void god() {
	int ch;
	close(a2g_write);
	close(a2r_read);
	int c;
	for(;;) {
		read(a2g_read, race, sizeof(*race));
		if(race -> winner != 0) break;
		sleep(race -> print_interval);
		if(kbhit()) {
			getchar();
			getchar();
			char conf , who;
			int newpos;
			take_input();
		} else {
			race -> god_intervenes = false;
			write(a2r_write, race, sizeof(*race));
		}
	}
	close(a2g_read);
	close(a2r_write);
}

void reporter() {
	close(a2h_read);
	close(a2t_read);
	close(a2g_read);
	close(a2r_write);
	race -> hare_pos = 0;
	race -> turt_pos = 0;
	print_race(race);
	Race *t = (struct Race*) malloc(sizeof(struct Race));
	Race *h = (struct Race*) malloc(sizeof(struct Race));
	Race *g = (struct Race*) malloc(sizeof(struct Race));
	int itr = 0;
	for(;;) {
		write(a2t_write, race, sizeof(*race));
		read(a2r_read, t, sizeof(*race));
		write(a2h_write, race, sizeof(*race));
		read(a2r_read, h, sizeof(*race));
		if(h -> hare_slept) {
			race -> turt_pos = h -> turt_pos;
		} else {
			race -> turt_pos = t -> turt_pos;
		}
		race -> hare_pos = h -> hare_pos;
		print_race(race);
		if(race -> turt_pos >= race -> distance) {
			race -> winner = TURTLE;
			break;
		} else if(race -> hare_pos >= race -> distance) {
			race -> winner = HARE;
			break;
		}
		write(a2g_write, race, sizeof(*race));
		read(a2r_read, race, sizeof(*race));
		if(race -> god_intervenes) {
			race -> god_intervenes = false;
			print_race(race);
		}
	}
	write(a2g_write, race, sizeof(*race));
	write(a2h_write, race, sizeof(*race));
	write(a2t_write, race, sizeof(*race));
	printf("Winner: %s\n", race -> winner == 1? "Hare" : "Turtle");
	close(a2h_write);
	close(a2t_write);
	close(a2r_read);
}

