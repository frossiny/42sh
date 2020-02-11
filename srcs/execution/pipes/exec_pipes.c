/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 20:32:11 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/29 15:19:45 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ast.h"
#include "execution.h"
#include "jobcontrol.h"
#include "builtins.h"

static t_pipel	*read_pipeline(t_pipel *pipeline, t_fd *fd)
{
	t_pipel		*pipe_start;

	pipe_start = pipeline;
	while (pipeline && pipeline->cmd)
	{
		pipeline->next ? pipe(fd->np) : 0;
		g_return = exec_pipe_cmd(pipeline, fd);
		pipeline->pid = g_pipe_pid;
		pipeline->next ? copy_tab(fd->op, fd->np) : 0;
		if (!pipeline->next)
			break ;
		pipeline = pipeline->next;
	}
	g_lpid = g_pipe_pid;
	return (pipe_start);
}

int				exec_pipes(t_anode *node, t_shell *shell, t_anode **cn)
{
	t_fd		fd;
	t_pipel		*pipeline;

	if (!(pipeline = exec_build_pipeline(node, shell, cn)))
		return (1);
	fd.sfd = dup(1);
	g_shell.current_pipel = read_pipeline(pipeline, &fd);
	exec_is_pipe_bg(pipeline) ? job_new_pipe(pipeline) : 0;
	dup2(fd.sfd, 1);
	close(fd.sfd);
	exec_signal_pipe(pipeline, SIGCONT);
	g_return = exec_end_pipes(pipeline, &fd);
	g_shell.current_pipel = NULL;
	exec_del_pipeline(pipeline);
	return (g_return);
}
