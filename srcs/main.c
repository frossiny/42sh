/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 11:43:47 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/01 19:37:02 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "shell.h"
#include "libft.h"

t_shell			g_shell;
t_cursor_pos	g_pos;
int				g_child;
int				g_ignore_signals;
int				g_return;
int				g_clear_buffer;
char			*g_pwd;

static void	init_default_vars(void)
{
	char	buff[8192];
	t_var	*pwd;
	t_var	*shlvl;
	char	*tmp;
	DIR		*dir;

	if ((pwd = var_get(g_shell.vars, "PWD")) && (dir = opendir(pwd->value)))
	{
		closedir(dir);
		g_pwd = ft_strdup(pwd->value);
	}
	else
	{
		getcwd(buff, 8192);
		g_pwd = ft_strdup(buff);
	}
	var_set(&g_shell.vars, "PWD", g_pwd, 1);
	if ((shlvl = var_get(g_shell.vars, "SHLVL"))
		&& (tmp = ft_itoa(ft_atoi(shlvl->value) + 1)))
	{
		var_set(&g_shell.vars, "SHLVL", tmp, 1);
		ft_strdel(&tmp);
	}
	else
		var_set(&g_shell.vars, "SHLVL", "1", 1);
}

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
	g_shell.lexer.tokens = NULL;
	g_shell.lexer.state = ST_GENERAL;
	g_shell.lexer.lstate = ST_GENERAL;
	g_shell.ast = NULL;
	g_shell.bin_ht.table = NULL;
}

int			main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	register_signals();
	shell_init(envp);
	init_default_vars();
	return (shell());
}
