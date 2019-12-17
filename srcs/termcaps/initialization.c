/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:59:12 by vsaltel           #+#    #+#             */
/*   Updated: 2019/12/17 15:38:09 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <term.h>
#include "shell.h"
#include "ft_printf.h"

int				termcaps_init(struct termios *prev_term)
{
	int				ret;
	char			*term_var;
	struct termios	term;

	g_shell.able_termcaps = 0;
	if (!isatty(0))
		return (2);
	tcgetattr(0, &term);
	if (prev_term)
	{
		*prev_term = term;
		if ((term_var = getenv("TERM"))
				&& (ret = tgetent(NULL, term_var)) != 1)
			return (0);
		else if ((ret = tgetent(NULL, "xterm-256color")) != 1)
			return (0);
	}
	term.c_lflag &= ~(ICANON | ECHO | IEXTEN | OPOST);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(g_shell.pgrp, TCSANOW, &term))
		return (0);
	g_shell.able_termcaps = 1;
	return (1);
}

void			restore_shell(struct termios prev_term)
{
	if (!isatty(0))
		return ;
	tcsetattr(g_shell.pgrp, TCSANOW, &prev_term);
}

void			free_termcaps(t_shell *shell)
{
	if (shell->able_termcaps)
	{
		overwrite_history(shell->history.lst);
		free_history(&(shell->history));
		restore_shell(shell->prev_term);
		free(g_pos.v_str);
		if (g_pos.o_input)
			free(g_pos.o_input);
	}
}

int				memset_all(char **str, t_history *history, t_cursor_pos *pos)
{
	g_clear_buffer = 0;
	*str = NULL;
	memset_history(history);
	if (!memset_pos(pos))
		return (0);
	return (1);
}
