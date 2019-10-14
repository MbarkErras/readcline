/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cline_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 00:18:02 by merras            #+#    #+#             */
/*   Updated: 2019/10/14 18:46:12 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readcline.h"

void	cline_history_motion(t_read *config)
{
	if (IS_DOWN(config->buffer) && config->history && !config->history->next)
	{
		while (config->position)
			move_left(config);
		tputs(tgetstr("cd", NULL), 1, _putchar);
		config->context = &config->input;
		cline_insert(config, "");
		while ((*config->context)[config->position])
			move_right(config);
		F_UNSET(config->flags, F_HISTORY);
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
		tputs(tgetstr("cd", NULL), 1, _putchar);
		config->context = (char **)&config->history->content;
		cline_insert(config, "");
		while ((*config->context)[config->position])
			move_right(config);
	}
	F_SET(config->flags, F_HISTORY);
}
