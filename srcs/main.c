/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 11:43:47 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/14 18:37:53 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_shell			g_shell;
t_cursor_pos	g_pos;
int				g_child;
int				g_ignore_signals;
int				g_return;
int				g_clear_buffer;

static void	shell_init(char *envp[])
{
	g_shell.able_termcaps = termcaps_init(&(g_shell.prev_term));
	g_child = 0;
	g_ignore_signals = 0;
	g_return = 0;
	g_shell.vars = var_init(envp);
	if (var_get(g_shell.vars, "HOME"))
		g_shell.history = get_history();
	else
		g_shell.history.lst = NULL;
	g_pos.v_str = NULL;
	g_shell.ast = NULL;
	g_shell.bin_ht.table = NULL;
}

int			main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	register_signals();
	shell_init(envp);
	return (shell());
}
