/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 20:32:11 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/14 18:41:59 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "shell.h"
#include "ast.h"
#include "utils.h"
#include "builtins.h"

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
	handle_redirections(pline->cmd->redir);
}

static int	execute_pipe_cmd(t_pipel *pline, t_fd *fd, t_shell *shell)
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
								cmd->args, var_build_env(shell->vars)) == -1)
			exit(EXIT_FAILURE);
	}
	else if (pline->previous)
	{
		close(fd->op[0]);
		close(fd->op[1]);
	}
	return (ret);
}

static int	execute_pipe_builtin(t_pipel *pline, t_fd *fd, t_shell *shell)
{
	t_builtin	builtin;
	t_cmd		*cmd;
	int			ret;
	int			sfd[3];

	cmd = pline->cmd;
	if (!is_builtin(cmd->exe->content))
		return (execute_pipe_cmd(pline, fd, shell));
	if (!(ret = validate_redirection(cmd->redir)))
		return (!ret);
	if (!(builtin = get_builtin(cmd->exe->content)).func)
		return (-1);
	if (cmd->redir)
	{
		sfd[0] = dup(0);
		sfd[1] = fd->sfd;
		sfd[2] = dup(2);
	}
	if (pline->next)
		dup2(fd->np[1], 1);
	handle_redirections(cmd->redir);
	ret = builtin.func(cmd, shell);
	cmd->redir ? restore_fd(sfd) : dup2(fd->sfd, 1);
	return (ret);
}

static void	end_pipes(t_childs *childs, t_fd *fd, t_shell *shell)
{
	int		ret;

	while (childs)
	{
		waitpid(childs->pid, &ret, 0);
		if (!childs->next)
		{
			if (WIFSIGNALED(ret))
				g_return = display_signal(ret);
			else
				g_return = WEXITSTATUS(ret);
		}
		childs = childs->next;
	}
	shell->able_termcaps ? termcaps_init(NULL) : 0;
	g_child = 0;
	close(fd->np[0]);
	close(fd->np[1]);
	close(fd->op[0]);
	close(fd->op[1]);
}

int			execute_pipes(t_anode *node, t_shell *shell, t_anode **cn)
{
	t_fd		fd;
	t_pipel		*pipeline;
	t_childs	*childs;

	if (!(pipeline = build_pipeline(node, shell, cn)))
		return (1);
	fd.sfd = dup(1);
	childs = NULL;
	get_pipes_docs(shell, pipeline);
	while (pipeline && pipeline->cmd)
	{
		pipeline->next ? pipe(fd.np) : 0;
		g_return = execute_pipe_builtin(pipeline, &fd, shell);
		child_add(&childs, g_child);
		pipeline->next ? copy_tab(fd.op, fd.np) : 0;
		if (!pipeline->next)
			break ;
		pipeline = pipeline->next;
	}
	dup2(fd.sfd, 1);
	close(fd.sfd);
	end_pipes(childs, &fd, shell);
	child_del(childs);
	del_pipeline(pipeline);
	return (g_return);
}
