/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cline_cursor_motion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 21:45:15 by merras            #+#    #+#             */
/*   Updated: 2019/10/11 01:01:51 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readcline.h"

void	move_right(t_read *config)
{
	config->buffer[0] = ESC;
	config->buffer[1] = '[';
	config->buffer[2] = 'C';
	cline_cursor_motion(config);
}

void	cline_cursor_motion(t_read *config)
{
	if (!(*config.input)[config->position + 1])
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
		printf("yoyo\n");
	}
	else
		tputs(tgetstr(IS_RIGHT(config.buffer) ? "nd" : "le", NULL), 1,
		_putchar);
}
