/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 11:43:47 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/05 14:59:00 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_printf.h"

t_shell			g_shell;
t_cursor_pos	g_pos;
int				g_child;
int				g_ignore_signals;
int				g_return;
int				g_clear_buffer;

static int	shell_init(char *envp[])
{
	if (!termcaps_init(&(g_shell.prev_term)))
	{
		ft_printf("42sh: can not load termcaps\n");
		ft_printf("Verify TERM variable \"TERM=xterm-256color\"\n");
		return (0);
	}
	g_child = 0;
	g_ignore_signals = 0;
	g_return = 0;
	g_shell.vars = var_init(envp);
	g_shell.alias = NULL;
	if (var_get(g_shell.vars, "HOME"))
		g_shell.history = get_history();
	else
		g_shell.history.lst = NULL;
	g_pos.v_str = NULL;
	g_shell.lexer.tokens = NULL;
	g_shell.lexer.state = ST_GENERAL;
	g_shell.lexer.lstate = ST_GENERAL;
	g_shell.ast = NULL;
	g_shell.bin_ht.table = NULL;
	return (1);
}

int			main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	register_signals();
	if (!shell_init(envp))
		return (1);
	return (shell());
}
