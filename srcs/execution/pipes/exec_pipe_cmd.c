/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 11:49:21 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/28 15:59:34 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "execution.h"
#include "jobcontrol.h"
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

static void	fork_child(t_pipel *pline, t_cmd *cmd, t_fd *fd)
{
	int		bg;

	bg = exec_is_pipe_bg(pline);
	unregister_signals();
	!bg && g_shell.able_termcaps ? restore_shell(g_shell.prev_term) : 0;
	bg ? setpgid(0, 0) : 0;
	init_fd(pline, fd->op, fd->np);
	if (execve(get_exe(&g_shell, cmd->exe->content, 1),
					cmd->args, var_build_env(cmd->tenv)) == -1)
		exit(EXIT_FAILURE);
}

int			exec_pipe_cmd(t_pipel *pline, t_fd *fd, t_shell *shell)
{
	t_cmd	*cmd;
	int		ret;

	cmd = pline->cmd;
	if (!(ret = validate_redirection(cmd->redir)))
		return (!ret);
	if ((ret = can_execute(cmd->exe->content, shell)))
		return (ret);
	g_child = fork();
	if (g_child == 0)
		fork_child(pline, cmd, fd);
	else if (pline->previous)
	{
		close(fd->op[0]);
		close(fd->op[1]);
	}
	return (ret);
}
