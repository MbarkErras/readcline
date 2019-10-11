/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cline_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 00:07:48 by merras            #+#    #+#             */
/*   Updated: 2019/10/11 00:52:50 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readcline.h"

void	terminal_insert(t_read *config, char *insertion)
{
	char	*inserted;
	int		length;
	int		i;

	i = 0;
	length = ft_strlen(inserted);
	tputs(tgetstr("cd", NULL), 1, _putchar);
	tputs(tgetstr("sc", NULL), 1, _putchar);
	while (i < config->position)
		ft_putchar((*config->input)[i]);
	ft_putstr(insertion);
	ft_putstr(*config.input + i);
	i = (*config.input)[config->position];
	(*config.input)[config->position] = 0;
	inserted = ft_strjoin((*config.input), insertion);
	(*config.input)[config->position] = i;
	inserted = ft_strjoin_free(inserted, *config.input + config->position, 1);
	free(*config.input);
	config->position += length;
	tputs(tgetstr("rc", NULL), 1, _putchar);
	i = -1;
	while (++i < length)
		move_right(config);
}
