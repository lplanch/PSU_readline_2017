/*
** EPITECH PROJECT, 2018
** get_key_readline.c
** File description:
** get the key of readline
*/

#include "readline.h"

static struct termios term, oterm;

int getch(void)
{
	int c = 0;

	tcgetattr(0, &oterm);
	memcpy(&term, &oterm, sizeof(term));
	term.c_lflag &= ~(ICANON | ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &term);
	c = getchar();
	tcsetattr(0, TCSANOW, &oterm);
	return (c);
}

int kbhit(void)
{
	int c = 0;

	tcgetattr(0, &oterm);
	memcpy(&term, &oterm, sizeof(term));
	term.c_lflag &= ~(ICANON | ECHO);
	term.c_cc[VMIN] = 0;
	term.c_cc[VTIME] = 1;
	tcsetattr(0, TCSANOW, &term);
	c = getchar();
	tcsetattr(0, TCSANOW, &oterm);
	if (c != -1) ungetc(c, stdin);
	return (c != -1 ? 1 : 0);
}

int kbesc(void)
{
	int c;

	if (!kbhit()) return KEY_ESCAPE;
	c = getch();
	if (c == '[') {
		switch (getch()) {
		case 'A':
			c = KEY_UP;
			break;
		case 'B':
			c = KEY_DOWN;
			break;
		case 'C':
			c = KEY_RIGHT;
			break;
		case 'D':
			c = KEY_LEFT;
			break;
		default:
			c = 0;
			break;
		}
	} else {
		c = 0;
	}
	if (c == 0) while (kbhit()) getch();
	return (c);
}

int get_key(void)
{
	int chr;

	chr = getch();
	return (chr == KEY_ESCAPE ? kbesc() : chr);
}
