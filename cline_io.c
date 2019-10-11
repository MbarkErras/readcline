/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cline_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 00:07:48 by merras            #+#    #+#             */
/*   Updated: 2019/10/11 05:18:39 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readcline.h"

void	cline_insert(t_read *config, char *insertion)
{
	char	*inserted;
	int		length;
	int		i;

	i = -1;
	length = ft_strlen(insertion);
	tputs(tgetstr("cd", NULL), 1, _putchar);
	tputs(tgetstr("sc", NULL), 1, _putchar);
	i = (*config->input)[config->position];
	(*config->input)[config->position] = 0;
	ft_putstr(insertion);
	ft_putstr(*config->input + config->position);
	inserted = ft_strjoin(*config->input, insertion);
	inserted = ft_strjoin_free(inserted, *config->input + config->position, 1);
	(*config->input)[config->position] = i;
	free(*config->input);
	*config->input = inserted;
	tputs(tgetstr("rc", NULL), 1, _putchar);
	length++;
	while (--length)
		move_right(config);
}
