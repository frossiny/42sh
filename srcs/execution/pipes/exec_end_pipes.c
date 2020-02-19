/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_end_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 11:42:11 by frossiny          #+#    #+#             */
/*   Updated: 2020/02/19 15:59:55 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "execution.h"

static void	get_return_code(void)
{
	if (WIFSIGNALED(g_lstatus))
		g_lstatus = g_lstatus != 18 ? display_signal(g_lstatus) : 0;
	else
		g_lstatus = WEXITSTATUS(g_lstatus);
}

static int	is_pipe_ended(t_pipel *pline)
{
	while (pline)
	{
		if (waitpid(pline->pid, &g_lstatus, WNOHANG) == 0)
			return (0);
		pline->pid = -1;
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
			!bg ? sigsuspend(NULL) : 0;
		if (is_pipe_ended(start))
			break ;
		pline = pline->next;
	}
	while (pline && pline->next)
		pline = pline->next;
	if (!bg)
		get_return_code();
	!bg && g_shell.able_termcaps ? termcaps_init(NULL) : 0;
	!bg ? tcsetpgrp(g_shell.pgrp, g_shell.pid) : 0;
	g_pipe_pid = 0;
	fd->np[0] != -1 ? close(fd->np[0]) : 0;
	fd->np[1] != -1 ? close(fd->np[1]) : 0;
	fd->op[0] != -1 ? close(fd->op[0]) : 0;
	fd->op[1] != -1 ? close(fd->op[1]) : 0;
	return (!g_shell.current_pipel ? 0 : g_lstatus);
}
