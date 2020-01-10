/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readcline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 18:51:57 by merras            #+#    #+#             */
/*   Updated: 2019/11/17 22:19:51 by merras           ###   ########.fr       */
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



void	read_sequence(t_read *config)
{
	if (IS_CURSOR_MOTION((config->buffer)))
		cline_cursor_motion(config);
	else if (IS_COPY(config->buffer) || IS_CUT(config->buffer) ||
		IS_PASTE(config->buffer))
		cline_clipboard(config);
	if (!F_GET(config->flags, F_CLIPBOARD))
	{
		if (IS_HISTORY_MOTION((config->buffer)))
			cline_history_motion(config);
		else if (IS_HOME(config->buffer) || IS_END(config->buffer))
			cline_home_end(config);
	}
}

int	read_character(t_read *config)
{
	if (IS_CLIPBOARD(config->buffer) && F_GET(config->flags, F_ESC))
	{
		config->buffer[1] = config->buffer[0];
		config->buffer[0] = 27;
		read_sequence(config);
		F_UNSET(config->flags, F_ESC);
	}
	else if (IS_ESC(config->buffer))
		F_SET(config->flags, F_ESC);
	if (!F_GET(config->flags, F_CLIPBOARD))
	{
		if (ft_isprint(config->buffer[0]))
			cline_insert(config, config->buffer);
		else if ((IS_DELETE(config->buffer) || IS_CTRLD(config->buffer)))
			return (cline_delete(config, 1));
		else if (IS_WORDLINE_MOTION(config->buffer))
			cline_wordline_motion(config);
		else if (IS_TAB(config->buffer))
			cline_tab_space(config);
	}
	return (0);
}

void	init_readcline(char *prompt, t_list *history,
		t_read *config)
{
	readcline_config(config);
	init_terminal(config->term);
	ft_putstr(prompt ? prompt : config->prompt);
	ft_bzero(config->buffer, 4);
	ioctl(1, TIOCGWINSZ, &(config->winsize));
	config->prompt_size = prompt ? config->prompt_size : ft_strlen(prompt);
	config->prompt = !prompt ? config->prompt : ft_strdup(prompt);
	config->history = !prompt ? config->history : list_head_tail(history, 1);
	//config->clipboard = !prompt ? config->clipboard : clipboard;
	config->flags = 0;
	if (!prompt)
		ft_strdel(&config->input);
	config->input = ft_strnew(0);
	config->context = &(config->input);
	config->position = 0;
	config->column = config->prompt_size + 1;
	config->row = 0;
	config->flags = 0;
}

void	flushcline(char *prompt)
{
	ft_putchar('\n');
	init_readcline(prompt, NULL, readcline_config(NULL));
}

char	*readcline(char *prompt, t_list *history, char **clipboard, char *term)
{
	t_read config;

	config.term = term;
	init_readcline(prompt, history, &config);
	config.clipboard = clipboard;
	while (read(0, config.buffer, 3))
	{
		if (IS_NEWLINE(config.buffer[0]))
		{
			while ((*config.context)[config.position])
				move_right(&config);
			ft_putchar('\n');
			break ;
		}
		if (IS_ONE_CHARACTER(config.buffer))
			if (read_character(&config))
			{
				ft_strdel(config.input);
				return (NULL);
			}
		else
			read_sequence(&config);
		ft_bzero(config.buffer, 4);
	}
	reset_input_mode();
	return (*config.context == config.input ? config.input :
	ft_strdup(*config.context));
}
