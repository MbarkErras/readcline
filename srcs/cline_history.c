/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cline_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 00:18:02 by merras            #+#    #+#             */
/*   Updated: 2019/10/20 22:32:09 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readcline.h"

void	restore_context(t_read *config)
{
	while (config->position)
		move_left(config);
	tputs(tgetstr("cd", NULL), 1, termcaps_putchar);
	config->context = &config->input;
	cline_insert(config, "");
	while ((*config->context)[config->position])
		move_right(config);
	F_UNSET(config->flags, F_HISTORY);
}

void	cline_history_motion(t_read *config)
{
	if (IS_DOWN(config->buffer) && config->history && !config->history->next)
	{
		restore_context(config);
		return ;
	}
	if (F_GET(config->flags, F_HISTORY) && config->history)
	{
		if (IS_UP(config->buffer) && !config->history->prev)
			return ;
		config->history = IS_UP(config->buffer) ? config->history->prev :
		config->history->next;
	}
	if (config->history)
	{
		while (config->position)
			move_left(config);
		tputs(tgetstr("cd", NULL), 1, termcaps_putchar);
		config->context = (char **)&config->history->content;
		cline_insert(config, "");
		while ((*config->context)[config->position])
			move_right(config);
	}
	F_SET(config->flags, F_HISTORY);
}
