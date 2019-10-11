/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readcline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 18:36:14 by merras            #+#    #+#             */
/*   Updated: 2019/10/11 07:43:24 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READCLINE_H
# define  READCLINE_H

# include "simplist.h"
# include "libft.h"
# include <sys/ioctl.h>
# include <term.h>

typedef struct
{
	int		prompt_size;
	t_list	*history;
	char	*clipboard;
	char	buffer[4];
	int		flags;
	char	**input;
	struct	winsize winsize;
	size_t	position;
	size_t	row;
	size_t	column;
}		t_read;

char	*readcline(char *prompt, t_list *history, char *clipboard);
t_read	init_readcline(char *prompt, t_list *history, char *clipboard);
void	flushcline(char *prompt);
t_read	*readcline_config(t_read *set);

void	cline_cursor_motion(t_read *config);
void	move_right(t_read *config);
void	move_left(t_read *config);

void	cline_insert(t_read *config, char *insertion);
void	cline_delete(t_read *config, int length);


int		_putchar(int c);

# define TAB '\t'
# define ESC 27
# define NEXT_WORD 0
# define PREVIOS_WORD 0 
# define UP_LINE 0
# define BOTTOM_LINE 0

# define IS_ONE_CHARACTER(x) !((x)[1])
# define IS_DELETE(x) ((x)[0] == 127)
# define IS_CTRLD(x) ((x)[0] == 4)
# define IS_NEWLINE(x) (x == '\n')
# define IS_NEWLINE(x) (x == '\n')
# define IS_WORD_MOTION(x) (x == NEXT_WORD || x == PREVIOUS_WORD)
# define IS_LINE_MOTION(x) (x == UP_LINE || x == BOTTOM_LINE)
# define IS_WORDLINE_MOTION(x) (IS_WORD_MOTION(x) || IS_LINE_MOTION(x))
# define IS_CSI(x) ((x)[0] == ESC && (x)[1] == '[')
# define IS_UP(x) (IS_CSI(x) && (x)[2] == 'A')
# define IS_DOWN(x) (IS_CSI(x) && (x)[2] == 'B')
# define IS_RIGHT(x) (IS_CSI(x) && (x)[2] == 'C')
# define IS_LEFT(x) (IS_CSI(x) && (x)[2] == 'D')
# define IS_CURSOR_MOTION(x) (IS_RIGHT(x) || IS_LEFT(x))
# define IS_HISTORY_MOTION(x) (IS_UP(x) || IS_DOWN(x))
# define IS_COPY(x) (IS_CSI(x) && (x)[2] == 'D') //
# define IS_CUT(x) (IS_CSI(x) && (x)[2] == 'D') //
# define IS_PASTE(x) (IS_CSI(x) && (x)[2] == 'D') //
# define IS_HOME(x) (IS_CSI(x) && (x)[2] == 'D') //
# define IS_END(x) (IS_CSI(x) && (x)[2] == 'D') //

#endif

