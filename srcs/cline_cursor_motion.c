/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cline_cursor_motion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 21:45:15 by merras            #+#    #+#             */
/*   Updated: 2019/10/20 22:33:35 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readcline.h"

size_t	line_length(char *string, int end)
{
	int	length;

	length = 0;
	while (end > -1 && string[end] != '\n')
	{
		length++;
		end--;
	}
	return (length);
}

void	cline_cursor_motion(t_read *config)
{
	if ((IS_RIGHT(config->buffer) && !(*config->context)[config->position]) ||
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
	if (config->column == 1)
		left_wrapper(config);
	else
	{
		tputs(tgetstr("le", NULL), 1, termcaps_putchar);
		if (F_GET(config->flags, F_CLIPBOARD))
		{
			ft_putchar((*config->context)[config->position - 1]);
			tputs(tgetstr("le", NULL), 1, termcaps_putchar);
		}
		config->position--;
		config->column--;
	}
}

void	move_right(t_read *config)
{
	if ((config->column == config->winsize.ws_col ||
	IS_NEWLINE((*config->context)[config->position + 1])))
	{
		tputs(tgetstr("do", NULL), 1, termcaps_putchar);
		config->position++;
		config->row++;
		config->column = 1;
	}
	else
	{
		if (F_GET(config->flags, F_CLIPBOARD))
		{
			tputs(tgetstr("us", NULL), 1, termcaps_putchar);
			ft_putchar((*config->context)[config->position]);
			tputs(tgetstr("ue", NULL), 1, termcaps_putchar);
		}
		else
			tputs(tgetstr("nd", NULL), 1, termcaps_putchar);
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
		while ((*config->context)[config->position])
			move_right(config);
	}
}
