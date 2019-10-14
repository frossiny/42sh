/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 11:43:47 by frossiny          #+#    #+#             */
/*   Updated: 2019/08/13 13:51:29 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_cursor_pos	g_pos;
int				g_child;
int				g_ignore_signals;
int				g_return;
int				g_clear_buffer;

int		main(int argc, char *argv[], char *envp[])
{
	t_shell		s_shell;

	(void)argc;
	(void)argv;
	s_shell.able_termcaps = termcaps_init(&(s_shell.prev_term));
	g_child = 0;
	g_ignore_signals = 0;
	g_return = 0;
	register_signals();
	s_shell.env = NULL;
	s_shell.env = copy_env(envp, 1);
	s_shell.ast = NULL;
	s_shell.bin_ht.table = NULL;
	if (exists_env(s_shell.env, "HOME"))
		s_shell.history = get_history();
	else
		s_shell.history.lst = NULL;
	g_pos.v_str = NULL;
	return (shell(&s_shell));
}
