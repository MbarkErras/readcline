/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cline_wordline_motion.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 12:54:30 by merras            #+#    #+#             */
/*   Updated: 2019/10/20 22:05:22 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readcline.h"

void	cline_wordline_motion_looper(t_read *config, int *i, int *j)
{
	if (IS_PREVIOUS_WORD(config->buffer) &&
		(((*config->context)[*i] == ' ' && *j == 1) || !*i))
	{
		*i = config->position - *i - (*i ? 1 : 0);
		while ((*i)--)
			move_left(config);
		return ;
	}
	if ((*config->context)[*i] == ' ')
	{
		while ((*config->context)[*i] == ' ')
			*i += IS_NEXT_WORD(config->buffer) ? 1 : -1;
		(*j)++;
	}
	if (IS_NEXT_WORD(config->buffer) && (*config->context)[*i] != ' ' &&
	*j == 1)
	{
		*i -= config->position;
		while ((*i)--)
			move_right(config);
		return ;
	}
	*i += IS_NEXT_WORD(config->buffer) ? 1 : -1;
}

void	cline_wordline_motion(t_read *config)
{
	int	i;
	int	j;

	i = config->position - 1;
	j = 0;
	while ((*config->context)[i])
		cline_wordline_motion_looper(config, &i, &j);
}
