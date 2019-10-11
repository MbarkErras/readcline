/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readcline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 18:51:57 by merras            #+#    #+#             */
/*   Updated: 2019/10/11 01:01:48 by merras           ###   ########.fr       */
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

t_read	init_readcline(char *prompt, t_list *history, char *clipboard)
{
	t_read	config;

	readcline_config(&config);
	ft_putstr(prompt);
	ft_bzero(config.buffer, 4);
	ioctl(1, TIOCGWINSZ, &(config.winsize));
	config.prompt_size = ft_strlen(prompt);
	config.history = history;
	config.clipboard = clipboard;
	config.flags = 0;
	config.input = malloc(sizeof(char *));
	*config.input = ft_strnew(0);
	config.position = 0;
	config.row = 0;
	config.column = config.prompt_size + 1;
	return (config);
}

void	read_character(t_read *config)
{
	if (ft_isprint((config->buffer[0]))
		cline_insert(config);
	/*else if (IS_DELETE((*config.buffer)[0]))
		cline_delete(config);
	else if (IS_WORDLINE_MOTION((*config.buffer)[0]))
		cline_wordline_motion_dispatcher(config);
	else if ((config->buffer[0] == TAB)
		cline_tab_space(config);
		*/
}

void	read_sequence(t_read *config)
{
	if (IS_CURSOR_MOTION((config->buffer)))
		cline_cursor_motion(config); // done
		/*
	else if (IS_HISTORY_MOTION((config->buffer
		cline_history_motion(config);
	else if (IS_COPY((config->buffer)
		continue ;
	else if (IS_CUT((config->buffer)
		continue ;
	else if (IS_PASTE((config->buffer)
		continue ;
	else if (IS_HOME((config->buffer)
		continue ;
	else if (IS_END((config->buffer)
		continue ;
		*/
}

char	*readcline(char *prompt, t_list *history, char *clipboarad)
{
	t_read config;

	config = init_readcline(prompt, history, clipboarad);
	while (read(0, config.buffer, 4))
	{
		if (IS_ONE_CHARACTER(config.buffer))
			read_character(&config);
		else
			read_sequence(&config);
		if (IS_NEWLINE(config.buffer[0]))
		{
			while ((*config.input)[config->position + 1])
				move_right(&config);
			break ;
		}
		ft_bzero(config.buffer, 4);
	}
	return (*config.input);
}
