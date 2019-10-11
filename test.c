#include <unistd.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include "readcline.h"

static void	set_input_mode(void)
{
	struct termios	tattr;

	/*
	 * 	if (!isatty(STDIN_FILENO))
	 * 			exit(ft_perror(EXEC_NAME, NULL, N_TTY));
	 * 				*/
	tcgetattr(STDIN_FILENO, &tattr);
	tattr.c_lflag &= ~(ICANON | ECHO);
	tattr.c_cc[VMIN] = 1;
	tattr.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &tattr);
}

int main()
{
	set_input_mode();
	printf("\n|%s|\n", readcline("$> ", NULL, NULL));
}
