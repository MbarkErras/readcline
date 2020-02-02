/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_configuration.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <merras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 21:18:12 by merras            #+#    #+#             */
/*   Updated: 2020/02/02 06:58:46 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readcline.h"

/*
** https://www.gnu.org/software/libc/manual/html_node/Noncanon-Example.html
*/

static int init_terminal_data(char *term)
{
	int		success;

	if (!term)
		return (ft_perror("readcline", NULL, N_TRM));
	success = tgetent(0, term);
	if (success < 0)
		return (ft_perror("readcline", NULL, A_TRM));
	if (!success)
		return (ft_perror("readcline", term, S_TRM));
	return (0);
}

static int	set_input_mode(void)
{
	struct termios	tattr;

	if (!isatty(STDIN_FILENO) || !isatty(2))
		return (ft_perror("readcline", NULL, N_TTY));
	tcgetattr(STDIN_FILENO, &tattr);
	tattr.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &tattr);
	return (0);
}

void		reset_input_mode(void)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &readcline_config(NULL)->saved_attr);
}

int		init_terminal(char *term)
{
	if (init_terminal_data(term))
		return (1);
	tcgetattr(STDIN_FILENO, &readcline_config(NULL)->saved_attr);
	if (set_input_mode())
		return (1);
	return (0);
}
