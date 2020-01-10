/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_end_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 11:42:11 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/10 14:20:23 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "execution.h"

void	exec_end_pipes(t_pipel *pline, t_childs *childs, t_fd *fd)
{
	int		ret;
	int		bg;

	bg = exec_is_pipe_bg(pline);
	while (childs)
	{
		waitpid(childs->pid, &ret, bg ? WNOHANG : 0);
		if (!bg && !childs->next)
		{
			if (WIFSIGNALED(ret))
				g_return = display_signal(ret);
			else
				g_return = WEXITSTATUS(ret);
		}
		childs = childs->next;
	}
	!bg && g_shell.able_termcaps ? termcaps_init(NULL) : 0;
	g_pipe = 0;
	close(fd->np[0]);
	close(fd->np[1]);
	close(fd->op[0]);
	close(fd->op[1]);
}
