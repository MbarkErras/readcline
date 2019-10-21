/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cline_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 00:07:48 by merras            #+#    #+#             */
/*   Updated: 2019/10/20 21:50:21 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readcline.h"

void	cline_tab_space(t_read *config)
{
	cline_insert(config, TABS_0(config->column % 4));
}

void	cline_insert(t_read *config, char *insertion)
{
	char	*inserted;
	int		length;
	int		i;

	length = ft_strlen(insertion);
	tputs(tgetstr("sc", NULL), 1, termcaps_putchar);
	i = (*config->context)[config->position];
	(*config->context)[config->position] = 0;
	ft_putstr(insertion);
	inserted = ft_strjoin(*config->context, insertion);
	(*config->context)[config->position] = i;
	ft_putstr(*config->context + config->position);
	inserted = ft_strjoin_free(inserted, *config->context + config->position,
	1);
	free(*config->context);
	*config->context = inserted;
	tputs(tgetstr("rc", NULL), 1, termcaps_putchar);
	length++;
	while (--length)
		move_right(config);
}

void	cline_delete_ctrld(t_read *config)
{
	int		i;

	if (!ft_strlen(*config->context))
		exit(EXIT_SUCCESS);
	tputs(tgetstr("cd", NULL), 1, termcaps_putchar);
	tputs(tgetstr("sc", NULL), 1, termcaps_putchar);
	i = (*config->context)[config->position];
	(*config->context)[config->position] = 0;
	*config->context = ft_strjoin_free(*config->context,
	*config->context + config->position + 1, 1);
	ft_putstr(*config->context + config->position);
	tputs(tgetstr("rc", NULL), 1, termcaps_putchar);
}

void	cline_delete(t_read *config, int length)
{
	int		i;

	if (IS_CTRLD(config->buffer))
	{
		cline_delete_ctrld(config);
		return ;
	}
	if (config->position < (size_t)length)
		return ;
	i = -1;
	while (++i < length)
		move_left(config);
	tputs(tgetstr("cd", NULL), 1, termcaps_putchar);
	tputs(tgetstr("sc", NULL), 1, termcaps_putchar);
	i = (*config->context)[config->position];
	(*config->context)[config->position] = 0;
	*config->context = ft_strjoin_free(*config->context, *config->context +
	config->position + length, 1);
	ft_putstr(*config->context + config->position);
	tputs(tgetstr("rc", NULL), 1, termcaps_putchar);
}
