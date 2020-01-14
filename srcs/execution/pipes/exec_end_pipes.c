/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_end_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 11:42:11 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/14 17:58:20 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "execution.h"

void	exec_end_pipes(t_pipel *pline, t_fd *fd)
{
	int		ret;
	int		bg;

	bg = exec_is_pipe_bg(pline);
	while (pline && g_shell.current_pipel)
	{
		waitpid(pline->pid, &ret, bg ? WNOHANG : 0);
		if (!bg && !pline->next)
		{
			if (WIFSIGNALED(ret))
				g_return = display_signal(ret);
			else
				g_return = WEXITSTATUS(ret);
		}
		pline = pline->next;
	}
	!bg && g_shell.able_termcaps ? termcaps_init(NULL) : 0;
	g_pipe_pid = 0;
	g_shell.current_pipel = NULL;
	close(fd->np[0]);
	close(fd->np[1]);
	close(fd->op[0]);
	close(fd->op[1]);
}
