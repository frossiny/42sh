/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 11:43:47 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/30 18:27:23 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_shell			g_shell;
t_cursor_pos	g_pos;
int				g_child;
int				g_ignore_signals;
int				g_return;
int				g_clear_buffer;

int		main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	g_shell.able_termcaps = termcaps_init(&(g_shell.prev_term));
	g_child = 0;
	g_ignore_signals = 0;
	g_return = 0;
	register_signals();
	g_shell.env = NULL;
	g_shell.env = copy_env(envp, 1);
	g_shell.ast = NULL;
	g_shell.bin_ht.table = NULL;
	if (exists_env(g_shell.env, "HOME"))
		g_shell.history = get_history();
	else
		g_shell.history.lst = NULL;
	g_pos.v_str = NULL;
	return (shell_init());
}
