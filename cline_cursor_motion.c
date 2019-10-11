/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cline_cursor_motion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 21:45:15 by merras            #+#    #+#             */
/*   Updated: 2019/10/11 07:38:02 by merras           ###   ########.fr       */
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

void	move_left(t_read *config)
{
	config->buffer[0] = ESC;
	config->buffer[1] = '[';
	config->buffer[2] = 'D';
	cline_cursor_motion(config);
}

void	move_right(t_read *config)
{
	config->buffer[0] = ESC;
	config->buffer[1] = '[';
	config->buffer[2] = 'C';
	cline_cursor_motion(config);
}

void		cline_cursor_motion(t_read *config)
{
	int	length;

	if ((IS_RIGHT(config->buffer) && !(*config->input)[config->position]) ||
		(IS_LEFT(config->buffer) && !config->position))
		return ;
	if (IS_RIGHT(config->buffer) &&
		(config->column == config->winsize.ws_row ||
		IS_NEWLINE((*config->input)[config->position + 1])))
	{
		tputs(tgetstr("do", NULL), 1, _putchar);
		config->position++;
		config->row++;
		config->column = 0;
	}
	else if (IS_LEFT(config->buffer) && config->column == 1)
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
		tputs(tgetstr(IS_RIGHT(config->buffer) ? "nd" : "le", NULL), 1,
		_putchar);
		config->position += IS_RIGHT(config->buffer) ? 1 : -1;
		config-> column += IS_RIGHT(config->buffer) ? 1 : -1;
	}
}
