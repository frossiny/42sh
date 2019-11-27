/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executables.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 13:26:37 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/27 18:48:41 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "ast.h"
#include "reader.h"
#include "utils.h"
#include "hashtable.h"
#include "builtins.h"

static int	exe_specials(t_cmd *cmd)
{
	int		ret;

	ret = 0;
	if (!cmd)
		return (1);
	if (cmd->tenv)
		ret = assign_vars(cmd);
	if (cmd->redir)
	{
		if (!get_here_doc(cmd->redir, &g_shell))
			return (EXIT_FAILURE);
		handle_redirections(cmd->redir, 1);
		close_here_docs(cmd->redir);
	}
	return (ret);
}

#include <stdio.h>

char	*reconstruct_command_jobs(char **command)
{
	int		i;
	int		e;
	char	*ret;

	i = 0;
	e = 0;
	while (command[e])
		i += ft_strlen(command[e++]) + 1;
	if (!(ret = ft_strnew(i)))
		return (NULL);
	e = 0;
	while (command[e])
	{
		ft_strcat(ret, command[e++]);
		ft_strcat(ret, " ");
	}
	return (ret);
}

static int	start_process(char *file, t_cmd *cmd, char **env)
{
	int		status;

	if (!get_here_doc(cmd->redir, &g_shell))
		return (EXIT_FAILURE);
	g_child = fork();
	if (cmd->is_bg && g_child)
	{
		g_shell.jobs.last_job->pid = g_child;
		ft_printf("[%d] %d\n", g_shell.jobs.last_job->job_number, g_child);
		g_shell.jobs.last_job->command = reconstruct_command_jobs(cmd->args);
	}
	if (!g_child)
	{
		unregister_signals();
		!cmd->is_bg && g_shell.able_termcaps ? restore_shell(g_shell.prev_term) : 0;
		cmd->is_bg ? setpgid(0, 0) : 0;
		handle_redirections(cmd->redir, 0);
		if (execve(file, cmd->args, env) == -1)
			exit(EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	close_here_docs(cmd->redir);
	if (g_child == -1)
		return (g_child = 0);
	waitpid(g_child, &status, cmd->is_bg ? WNOHANG : 0);
	!cmd->is_bg && g_shell.able_termcaps ? termcaps_init(NULL) : 0;
	g_child = 0;
	if (WIFSIGNALED(status))
		return (display_signal(status));
	return (WEXITSTATUS(status));
}

static int	start(t_cmd *cmd, char **env)
{
	int		ret;
	char	*file;

	if (!cmd->allow_builtins || (ret = handle_builtin(cmd, &g_shell)) == -1)
	{
		if (!(file = get_exe(&g_shell, cmd->exe->content, 1)))
			return (127);
		if ((ret = can_execute(cmd->exe->content, &g_shell)))
		{
			free(file);
			return (ret);
		}
		ret = start_process(file, cmd, env);
		free(file);
	}
	return (ret);
}

int			execute(t_cmd *cmd)
{
	int		ret;
	char	**env;

	if (!cmd)
		return (1);
	if (ast_build_args(cmd, g_shell.vars) < 0)
		return (1);
	cmd->redir = parse_redirections(cmd->tokens);
	if (!validate_redirection(cmd->redir))
		return (1);
	if (!cmd->exe)
		return (exe_specials(cmd));
	var_merge(&(cmd->tenv), g_shell.vars);
	env = var_build_env(cmd->tenv);
	ret = start(cmd, env);
	var_destroy(&(cmd->tenv));
	ft_strddel(&env);
	return (ret);
}
