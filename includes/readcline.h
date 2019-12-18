/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readcline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 18:36:14 by merras            #+#    #+#             */
/*   Updated: 2019/11/17 21:30:44 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READCLINE_H
# define READCLINE_H

# include "simplist.h"
# include "centropy.h"
# include <sys/ioctl.h>
# include <term.h>

# define EXEC_NAME "readcline"

typedef struct		s_read
{
	int				prompt_size;
	char			*prompt;
	t_list			*history;
	char			**clipboard;
	char			buffer[4];
	char			**context;
	char			*input;
	struct winsize	winsize;
	size_t			position;
	size_t			row;
	size_t			column;
	char			flags;
	int				clipboard_offset;
	struct termios	saved_attr;
}					t_read;

char				*readcline(char *prompt, t_list *history,
					char **clipboard, char *term);
void				init_readcline(char *prompt, t_list *hisory,
					t_read *config, char *term);
void				flushcline(char *prompt);
t_read				*readcline_config(t_read *set);

void				cline_cursor_motion(t_read *config);
void				move_right(t_read *config);
void				move_left(t_read *config);
void				left_wrapper(t_read *config);
void				cline_wordline_motion(t_read *config);
void				cline_tab_space(t_read *config);
void				cline_home_end(t_read *config);
size_t				line_length(char *string, int end);

void				cline_insert(t_read *config, char *insertion);
void				cline_delete(t_read *config, int length);
void				cline_delete_ctrld(t_read *config);

void				cline_clipboard(t_read *config);

void				cline_history_motion(t_read *config);

int					termcaps_putchar(int c);

void				init_terminal(char *term);
void				reset_input_mode(void);

# define ESC 27
# define PREVIOUS_WORD 6
# define NEXT_WORD 7
# define UP_LINE 5
# define BOTTOM_LINE 23

# define IS_ONE_CHARACTER(x) !((x)[1])
# define IS_DELETE(x) ((x)[0] == 127)
# define IS_CTRLD(x) ((x)[0] == 4)
# define IS_NEWLINE(x) (x == '\n')
# define IS_TAB(x) ((x)[0] == '\t')
# define IS_WORD_MOTION(x) ((x)[0] == NEXT_WORD || (x)[0]== PREVIOUS_WORD)
# define IS_NEXT_WORD(x) ((x)[0] == NEXT_WORD)
# define IS_PREVIOUS_WORD(x) ((x)[0] == PREVIOUS_WORD)
# define IS_LINE_MOTION(x) ((x)[0] == UP_LINE || (x)[0] == BOTTOM_LINE)
# define IS_WORDLINE_MOTION(x) (IS_WORD_MOTION(x) || IS_LINE_MOTION(x))
# define IS_CSI(x) ((x)[0] == ESC && (x)[1] == '[')
# define IS_UP(x) (IS_CSI(x) && (x)[2] == 'A')
# define IS_DOWN(x) (IS_CSI(x) && (x)[2] == 'B')
# define IS_RIGHT(x) (IS_CSI(x) && (x)[2] == 'C')
# define IS_LEFT(x) (IS_CSI(x) && (x)[2] == 'D')
# define IS_CURSOR_MOTION(x) (IS_RIGHT(x) || IS_LEFT(x))
# define F_HISTORY 2
# define IS_HISTORY_MOTION(x) (IS_UP(x) || IS_DOWN(x))
# define F_CLIPBOARD 1
# define IS_CLIPBOARD(x) ((x)[0] == 'x' || (x)[0] == 'c' || (x)[0] == 'v')
# define IS_COPY(x) ((x)[0] == ESC && (x)[1] == 'c')
# define IS_CUT(x) ((x)[0] == ESC && (x)[1] == 'x')
# define IS_PASTE(x) ((x)[0] == ESC && (x)[1] == 'v')
# define IS_HOME(x) (IS_CSI(x) && (x)[2] == 'H')
# define IS_END(x) (IS_CSI(x) && (x)[2] == 'F')

# define F_ESC 0
# define IS_ESC(x) ((x)[0] == ESC)

# define F_GET(x, f) (x & (1 << f))
# define F_BGET(x, f) (x & f)
# define F_SET(x, f) (x |= (1 << f))
# define F_BSET(x, f) (x |= f)
# define F_UNSET(x, f) (x &= ~(1 << f))
# define F_BUNSET(x, f) (x &= ~f)

# define F_INPUT 7

# define TABS_3(x) (x == 3 ? " " : "")
# define TABS_2(x) (x == 2 ? "  " : TABS_3(x))
# define TABS_1(x) (x == 1 ? "   " : TABS_2(x))
# define TABS_0(x) (x == 0 ? "    " : TABS_1(x))

/*
** ERROR HANDLING
*/

int					ft_perror(char *command, char *arg, int err);

# define N_TRM 1
# define A_TRM 2
# define S_TRM 3
# define N_TTY 4

# define N_TRM_T ": specify a terminal type with setenv TERM <yourtype>"
# define A_TRM_T ": could not access the termcap data base"
# define S_TRM_T ": terminal type is not defined: "
# define N_TTY_T ": not a terminal"

#endif
