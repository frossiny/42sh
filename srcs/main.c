/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 11:43:47 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/23 17:41:29 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "shell.h"
#include "libft.h"
#include "history.h"
#include "ft_printf.h"

t_shell			g_shell;
t_cursor_pos	g_pos;
int				g_child;
int				g_pipe_pid;
int				g_lstatus;
int				g_ignore_signals;
int				g_return;
int				g_lpid;
int				g_clear_buffer;
char			*g_pwd;

static void	init_default_vars(char *tmp)
{
	char	buff[MAX_PWD_LEN];
	t_var	*pwd;
	t_var	*shlvl;
	DIR		*dir;

	if ((pwd = var_get(g_shell.vars, "PWD"))
		&& (dir = opendir(pwd->value)))
	{
		closedir(dir);
		g_pwd = ft_strdup(pwd->value);
	}
	else
	{
		getcwd(buff, MAX_PWD_LEN);
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

static int	shell_config(char *envp[])
{
	g_shell.stopped_jobs = 0;
	g_shell.pid = getpid();
	g_shell.pgrp = STDIN_FILENO;
	g_shell.vars = var_init(envp);
	g_shell.alias = NULL;
	g_shell.current_cmd = NULL;
	g_shell.history = get_history();
	g_pos.v_str = NULL;
	g_shell.lexer.tokens = NULL;
	g_shell.lexer.state = ST_GENERAL;
	g_shell.lexer.lstate = ST_GENERAL;
	g_shell.ast = NULL;
	g_shell.bin_ht.table = NULL;
	g_shell.jobs.index = 1;
	g_shell.jobs.len = 0;
	g_shell.jobs.minus = NULL;
	g_shell.jobs.plus = NULL;
	g_shell.jobs.lst = NULL;
	g_shell.jobs.last_job = NULL;
	return (1);
}

static int	shell_init(void)
{
	g_child = 0;
	g_pipe_pid = 0;
	g_ignore_signals = 0;
	g_return = 0;
	g_lpid = -1;
	g_lstatus = 0;
	if (isatty(STDIN_FILENO))
	{
		if (setpgid(g_shell.pid, g_shell.pid) < 0 \
			|| tcsetpgrp(g_shell.pgrp, g_shell.pid))
		{
			ft_dprintf(2, \
				"42sh: Couldn't put the shell in its own process group");
			exit(1);
		}
	}
	if (!termcaps_init(&(g_shell.prev_term)))
	{
		ft_printf("42sh: can not load termcaps\n");
		ft_printf("Verify TERM variable \"TERM=xterm-256color\"\n");
		return (0);
	}
	return (1);
}

int			main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	register_signals();
	if (!shell_config(envp) || !shell_init())
		return (0);
	init_default_vars(NULL);
	return (shell());
}
