/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readcline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 18:51:57 by merras            #+#    #+#             */
/*   Updated: 2019/10/10 21:57:25 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readcline.h"

t_read	*readcline_config(t_read *set)
{
	static t_read	*config = NULL;

	if (set)
		config = set;
	return (config);
}

t_read	init_readcline(char *prompt, t_list *history, char *clipboarad)
{
	t_read	config;

	readcline_config(&config);
	ft_putstr(prompt);
	ft_bzero(config.buffer);
	config.prompt_size = ft_strlen(prompt);
	config.history = history;
	config.clipboard = clipboard;
	config.flags = 0;
	*config.input = ft_strnew(0);
	return (config);
}

void	read_character(t_read *config)
{
	if (ft_isprint((*config.input)[0]))
		*config.input = ft_strjoin_free(*config.in, buffer, 1);
	else if (IS_DELETE((*config.buffer)[0]))
		cline_delete(config);
	else if (IS_WORDLINE_MOTION((*config.buffer)[0]))
		cline_wordline_motion_dispatcher(config);
	else if ((*config.input)[0] == TAB)
		cline_tab_space(config);
}

void	read_sequence(t_read config)
{
	if (IS_CURSOR_MOTION((*config.input))
		cline_cursor_motion(config);
	else if (IS_HISTORY_MOTION((*config.input))
		cline_history_motion(config);
	else if (IS_COPY((*config.input)))
		continue ;
	else if (IS_CUT((*config.input)))
		continue ;
	else if (IS_PASTE((*config.input)))
		continue ;
	else if (IS_HOME((*config.input)))
		continue ;
	else if (IS_END((*config.input)))
		continue ;
}

char	*readcline(char *prompt, t_list *history, char *clipboarad)
{
	t_read config;

	config = init_readcline(prompt, history, clipboarad);
	while (read(0, config.buffer, 4))
	{
		if (IS_ONE_CHARACTER((*config.input)))
			read_character(config);
		else
			read_sequence(config);
		if (config.buffer[0] == NEWLINE)
		{
			//go the end;
			break ;
		}
		ft_bzero(config.buffer);
	}
	return (*config.in);
}
