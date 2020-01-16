/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_end_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 11:42:11 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/16 14:10:12 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "execution.h"

static int	is_pipe_ended(t_pipel *pline)
{
	while (pline)
	{
		if (waitpid(pline->pid, &g_last_status, WNOHANG) == 0)
			return (0);
		pline = pline->next;
	}
	return (1);
}

int			exec_end_pipes(t_pipel *pline, t_fd *fd)
{
	t_pipel	*start;
	int		bg;

	start = pline;
	bg = exec_is_pipe_bg(pline);
	while (pline && g_shell.current_pipel)
	{
		if (pline->pid)
			!bg ? pause() : 0;
		if (is_pipe_ended(start))
			break ;
		pline = pline->next;
	}
	while (pline && pline->next)
		pline = pline->next;
	if (!bg)
	{
		if (WIFSIGNALED(g_last_status))
			g_last_status = g_last_status != 18 ? display_signal(g_last_status) : 0;
		else
			g_last_status = WEXITSTATUS(g_last_status);
	}
	!bg && g_shell.able_termcaps ? termcaps_init(NULL) : 0;
	g_pipe_pid = 0;
	close(fd->np[0]);
	close(fd->np[1]);
	close(fd->op[0]);
	close(fd->op[1]);
	return (!g_shell.current_pipel ? 0 : g_last_status);
}
