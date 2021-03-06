/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 11:49:21 by frossiny          #+#    #+#             */
/*   Updated: 2020/02/19 17:47:53 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "execution.h"
#include "jobcontrol.h"
#include "ast.h"
#include "builtins.h"

static int	init_fd(t_pipel *pline, int op[], int np[])
{
	if (pline->previous)
	{
		dup2(op[0], 0);
		close(op[0]);
		close(op[1]);
	}
	if (pline->next)
	{
		close(np[0]);
		dup2(np[1], 1);
		close(np[1]);
	}
	return (handle_redirections(pline->cmd->redir, 0));
}

static int	fork_builtin(t_cmd *cmd)
{
	t_builtin	builtin;
	int			ret;

	if (!(builtin = get_builtin(cmd->exe->content)).func)
	{
		u_free_shell(0);
		return (-1);
	}
	ret = builtin.func(cmd, &g_shell);
	u_free_shell(0);
	return (ret);
}

static void	fork_child(t_pipel *pline, t_cmd *cmd, t_fd *fd)
{
	int		bg;
	char	*file;
	int		error;

	bg = exec_is_pipe_bg(pline);
	unregister_signals();
	!bg && g_shell.able_termcaps ? restore_shell(g_shell.prev_term) : 0;
	if (!(init_fd(pline, fd->op, fd->np)) || !cmd->exe)
	{
		u_free_shell(0);
		exit(EXIT_FAILURE);
	}
	if (is_builtin(cmd->exe->content))
		exit(fork_builtin(cmd));
	if (!(file = exec_get_file(cmd, &error, 1)))
	{
		u_free_shell(0);
		exit(error);
	}
	execve(file, cmd->args, var_build_env(cmd->tenv));
	u_free_shell(0);
	exit(EXIT_FAILURE);
}

int			exec_pipe_cmd(t_pipel *pline, t_fd *fd)
{
	t_cmd	*cmd;

	cmd = pline->cmd;
	g_pipe_pid = fork();
	if (g_pipe_pid == -1)
		return (-1);
	else if (g_pipe_pid == 0)
		fork_child(pline, cmd, fd);
	else if (pline->previous)
	{
		close(fd->op[0]);
		close(fd->op[1]);
	}
	if (!pline->previous && !exec_is_pipe_bg(pline))
		tcsetpgrp(g_shell.pgrp, g_pipe_pid);
	kill(-g_pipe_pid, SIGSTOP);
	return (1);
}
