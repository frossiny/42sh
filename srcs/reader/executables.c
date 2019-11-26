/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executables.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 13:26:37 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/26 17:30:33 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "shell.h"
#include "ast.h"
#include "utils.h"
#include "hashtable.h"
#include "builtins.h"

static int	exe_assignements(t_cmd *cmd)
{
	t_var	*cur;

	cur = cmd->tenv;
	while (cur)
	{
		var_set(&(g_shell.vars), cur->key, cur->value, 0);
		cur = cur->next;
	}
	var_destroy(&(cmd->tenv));
	return (0);
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
	if (g_shell.jobs && g_shell.jobs->is_jobs && g_child)
	{
		//to put after the exec
		g_shell.jobs->last_job->pid = g_child;
		ft_printf("[%d] %d\n", g_shell.jobs->last_job->job_number,
		g_child);
		g_shell.jobs->last_job->command = reconstruct_command_jobs(cmd->args);
	}
	if (!g_child)
	{
		if (g_shell.jobs && g_shell.jobs->is_jobs) // FOR TEST ONLY
			exit(EXIT_SUCCESS); // FOR TEST ONLY
		unregister_signals();
		g_shell.able_termcaps ? restore_shell(g_shell.prev_term) : 0;
		handle_redirections(cmd->redir);
		if (execve(file, cmd->args, env) == -1)
			exit(EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	close_here_docs(cmd->redir);
	if (g_child == -1)
		return (g_child = 0);
	waitpid(g_child, &status, 0);
	g_shell.able_termcaps ? termcaps_init(NULL) : 0;
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
	if (build_args(cmd, g_shell.vars) < 1)
		return (1);
	if (!cmd->exe && cmd->tenv)
		return (exe_assignements(cmd));
	cmd->redir = parse_redirections(cmd->exe);
	if (!validate_redirection(cmd->redir))
		return (1);
	//var_merge(&(cmd->tenv), g_shell.vars); //disabled because breaking hashtable
	env = var_build_env(cmd->tenv);
	ret = start(cmd, env);
	var_destroy(&(cmd->tenv));
	ft_strddel(&env);
	return (ret);
}
