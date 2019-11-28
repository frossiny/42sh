/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 20:32:11 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/28 11:57:43 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ast.h"
#include "execution.h"
#include "builtins.h"

int			exec_pipes(t_anode *node, t_shell *shell, t_anode **cn)
{
	t_fd		fd;
	t_pipel		*pipeline;
	t_childs	*childs;

	if (!(pipeline = exec_build_pipeline(node, shell, cn)))
		return (1);
	fd.sfd = dup(1);
	childs = NULL;
	exec_get_pipes_docs(shell, pipeline);
	while (pipeline && pipeline->cmd)
	{
		pipeline->next ? pipe(fd.np) : 0;
		g_return = exec_pipe_builtin(pipeline, &fd, shell);
		exec_child_add(&childs, g_child);
		pipeline->next ? copy_tab(fd.op, fd.np) : 0;
		if (!pipeline->next)
			break ;
		pipeline = pipeline->next;
	}
	dup2(fd.sfd, 1);
	close(fd.sfd);
	exec_end_pipes(childs, &fd);
	exec_child_del(childs);
	exec_del_pipeline(pipeline);
	return (g_return);
}