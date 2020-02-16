/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 20:32:11 by frossiny          #+#    #+#             */
/*   Updated: 2020/02/16 14:51:12 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ast.h"
#include "execution.h"
#include "jobcontrol.h"
#include "builtins.h"

static void	init_fd(t_fd *fd)
{
	fd->np[0] = -1;
	fd->np[1] = -1;
	fd->op[0] = -1;
	fd->op[1] = -1;
}

static void	read_pipeline(t_pipel *pipeline, t_fd *fd)
{
	g_shell.current_pipel = pipeline;
	while (pipeline)
	{
		pipeline->next ? pipe(fd->np) : 0;
		if ((g_return = exec_pipe_cmd(pipeline, fd)) == -1)
		{
			ft_printf("Error: fork failed\n");
			break ;
		}
		pipeline->pid = g_pipe_pid;
		pipeline->next ? copy_tab(fd->op, fd->np) : 0;
		if (!pipeline->next)
			break ;
		pipeline = pipeline->next;
	}
	g_lpid = g_pipe_pid;
}

int			exec_pipes(t_anode *node, t_shell *shell, t_anode **cn)
{
	t_fd		fd;
	t_pipel		*pipeline;

	if (!(pipeline = exec_build_pipeline(node, shell, cn)))
		return (1);
	init_fd(&fd);
	read_pipeline(pipeline, &fd);
	exec_is_pipe_bg(pipeline) ? job_new_pipe(pipeline) : 0;
	exec_signal_pipe(pipeline, SIGCONT);
	g_return = exec_end_pipes(pipeline, &fd);
	g_shell.current_pipel = NULL;
	exec_del_pipeline(pipeline);
	return (g_return);
}
