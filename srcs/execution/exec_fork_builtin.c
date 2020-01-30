/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fork_builtin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 10:35:21 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/30 17:34:52 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "builtins.h"
#include "execution.h"
#include "jobcontrol.h"
#include "utils.h"

static int	free_exit(t_var **env, int error)
{
	var_destroy(env);
	u_free_shell(0);
	exit(error);
	return (error);
}

int			exec_fork_builtin(t_cmd *cmd)
{
	t_builtin	builtin;
	int			status;

	if (!(builtin = get_builtin(cmd->exe->content)).func)
		return (-1);
	if ((g_child = fork()) > 0 && cmd->is_bg)
		job_new(cmd, g_child);
	if (!g_child)
	{
		unregister_signals();
		setpgid(0, 0);
		if (!(handle_redirections(cmd->redir, 0)))
			exit(free_exit(&(cmd->tenv), EXIT_FAILURE));
		status = builtin.func(cmd, &g_shell);
		exit(free_exit(&(cmd->tenv), status));
	}
	if (g_child == -1)
		return (g_child = 0);
	waitpid(g_child, &status, WNOHANG);
	g_child = 0;
	return (0);
}
