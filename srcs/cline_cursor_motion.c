/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cline_cursor_motion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 21:45:15 by merras            #+#    #+#             */
/*   Updated: 2019/10/12 21:45:30 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readcline.h"

static size_t	line_length(char *string, int i)
{
	int	length;

	length = 0;
	while (i || string[i] == '\n')
		i--;
	while (string[i] || string[i] == '\n')
		length++;
	return (length);
}

void		cline_cursor_motion(t_read *config)
{
	if ((IS_RIGHT(config->buffer) && !(*config->input)[config->position]) ||
		(IS_LEFT(config->buffer) && (!config->position ||
			(F_GET(config->flags, F_CLIPBOARD) &&
			config->position == (size_t)config->clipboard_offset))))
		return ;
	if (IS_RIGHT(config->buffer))
		move_right(config);
	else
		move_left(config);
}

void	move_left(t_read *config)
{
	int	length;

	if (config->column == 1)
	{
		length = line_length(*config->input, config->position);
		tputs(tgetstr("up", NULL), 1, _putchar);
		tputs(tparm(tgetstr("RI", NULL), length > config->winsize.ws_col ?
		config->winsize.ws_col : length), 1, _putchar);
		config->position--;
		config->row--;
		config->column = length > config->winsize.ws_col ?
		config->winsize.ws_col : length;
	}
	else
	{
		tputs(tgetstr("le", NULL), 1, _putchar);
		if (F_GET(config->flags, F_CLIPBOARD))
		{
			ft_putchar((*config->input)[config->position - 1]);
			tputs(tgetstr("le", NULL), 1, _putchar);
		}
		config->position--;
		config->column--;
	}
}

void	move_right(t_read *config)
{
	if ((config->column == config->winsize.ws_row ||
	IS_NEWLINE((*config->input)[config->position + 1])))
	{
		tputs(tgetstr("do", NULL), 1, _putchar);
		config->position++;
		config->row++;
		config->column = 0;
	}
	else
	{
		if (F_GET(config->flags, F_CLIPBOARD))
		{
			tputs(tgetstr("us", NULL), 1, _putchar);
			ft_putchar((*config->input)[config->position]);
			tputs(tgetstr("ue", NULL), 1, _putchar);
		}
		else
			tputs(tgetstr("nd", NULL), 1, _putchar);
		config->position++;
		config->column++;
	}
}

void	cline_home_end(t_read *config)
{
	if (IS_HOME(config->buffer))
	{
		while (config->position)
			move_left(config);
	}
	else
	{
		while ((*config->input)[config->position])
			move_right(config);
	}
}
