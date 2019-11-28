/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 11:49:21 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/28 11:56:51 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "execution.h"
#include "ast.h"

static void	init_fd(t_pipel *pline, int op[], int np[])
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
	handle_redirections(pline->cmd->redir, 0);
}

int		exec_pipe_cmd(t_pipel *pline, t_fd *fd, t_shell *shell)
{
	t_cmd	*cmd;
	int		ret;

	cmd = pline->cmd;
	if (!(ret = validate_redirection(cmd->redir)))
		return (!ret);
	if ((ret = can_execute(cmd->exe->content, shell)))
		return (ret);
	if ((g_child = fork()) == 0)
	{
		unregister_signals();
		shell->able_termcaps ? restore_shell(shell->prev_term) : 0;
		init_fd(pline, fd->op, fd->np);
		if (execve(get_exe(shell, cmd->exe->content, 1),
								cmd->args, var_build_env(cmd->tenv)) == -1)
			exit(EXIT_FAILURE);
	}
	else if (pline->previous)
	{
		close(fd->op[0]);
		close(fd->op[1]);
	}
	return (ret);
}
