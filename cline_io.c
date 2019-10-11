/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cline_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 00:07:48 by merras            #+#    #+#             */
/*   Updated: 2019/10/11 22:05:01 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readcline.h"

static char	*tab_spaces(int offset)
{
	if (!offset)
		return ("    ");
	if (offset == 1)
		return ("   ");
	if (offset == 2)
		return ("  ");
	if (offset == 3)
		return (" ");
	if (offset == 4)
		return (" ");
	else
		return ("essketit");
}

void	cline_tab_space(t_read *config)
{
	cline_insert(config, tab_spaces(config->column % 4));
}

void	cline_insert(t_read *config, char *insertion)
{
	char	*inserted;
	int		length;
	int		i;

	length = ft_strlen(insertion);
	tputs(tgetstr("sc", NULL), 1, _putchar);
	i = (*config->input)[config->position];
	(*config->input)[config->position] = 0;
	ft_putstr(insertion);
	inserted = ft_strjoin(*config->input, insertion);
	(*config->input)[config->position] = i;
	ft_putstr(*config->input + config->position);
	inserted = ft_strjoin_free(inserted, *config->input + config->position, 1);
	free(*config->input);
	*config->input = inserted;
	tputs(tgetstr("rc", NULL), 1, _putchar);
	length++;
	while (--length)
		move_right(config);
}

void	cline_delete_ctrld(t_read *config)
{
	int		i;

	if (!ft_strlen(*config->input))
		exit(EXIT_SUCCESS);
	tputs(tgetstr("cd", NULL), 1, _putchar);
	tputs(tgetstr("sc", NULL), 1, _putchar);
	i = (*config->input)[config->position];
	(*config->input)[config->position] = 0;
	*config->input = ft_strjoin_free(*config->input,
	*config->input + config->position + 1, 1);
	ft_putstr(*config->input + config->position);
	tputs(tgetstr("rc", NULL), 1, _putchar);
}

void	cline_delete(t_read *config, int length)
{
	int		i;

	if (IS_CTRLD(config->buffer))
	{
		cline_delete_ctrld(config);	
		return ;
	}
	if (config->position < length)
		return ;
	i = -1;
	while (++i < length)
		move_left(config);
	tputs(tgetstr("cd", NULL), 1, _putchar);
	tputs(tgetstr("sc", NULL), 1, _putchar);
	i = (*config->input)[config->position];
	(*config->input)[config->position] = 0;
	*config->input = ft_strjoin_free(*config->input, *config->input +
	config->position + length, 1);
	ft_putstr(*config->input + config->position);
	tputs(tgetstr("rc", NULL), 1, _putchar);
}
