/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_configuration.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 21:18:12 by merras            #+#    #+#             */
/*   Updated: 2019/11/17 22:19:56 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readcline.h"

/*
** https://www.gnu.org/software/libc/manual/html_node/Noncanon-Example.html
*/

static void	init_terminal_data(void)
{
	char	*termtype;
	int		success;

	termtype = getenv("TERM");
	if (!termtype)
		exit(ft_perror(EXEC_NAME, NULL, N_TRM));
	success = tgetent(0, termtype);
	if (success < 0)
		exit(ft_perror(EXEC_NAME, NULL, A_TRM));
	if (!success)
		exit(ft_perror(EXEC_NAME, termtype, S_TRM));
}

static void	set_input_mode(void)
{
	struct termios	tattr;

	if (!isatty(STDIN_FILENO) || !isatty(2))
		exit(ft_perror(EXEC_NAME, NULL, N_TTY));
	tcgetattr(STDIN_FILENO, &tattr);
	tattr.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &tattr);
}

void		reset_input_mode(void)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &readcline_config(NULL)->saved_attr);
}

void		init_terminal(void)
{
	init_terminal_data();
	tcgetattr(STDIN_FILENO, &readcline_config(NULL)->saved_attr);
	set_input_mode();
}