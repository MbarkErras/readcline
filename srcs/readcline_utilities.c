/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readcline_utilities.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 21:53:32 by merras            #+#    #+#             */
/*   Updated: 2019/10/21 02:39:50 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readcline.h"

void	left_wrapper(t_read *config)
{
	int length;

	length = line_length(*config->context, config->position) %
		config->winsize.ws_col;
	tputs(tgetstr("up", NULL), 1, termcaps_putchar);
	tputs(tparm(tgetstr("RI", NULL),
				(*config->context)[config->position - 1]
				== '\n' ? length : config->winsize.ws_col), 1,
	termcaps_putchar);
	config->position--;
	config->row--;
	config->column = (*config->context)[config->position - 1] == '\n' ?
		length : config->winsize.ws_col;
}
