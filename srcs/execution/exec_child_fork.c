/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child_fork.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 11:08:12 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/08 11:20:13 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "execution.h"

int		exec_child_fork(char *file, t_cmd *cmd, char **env)
{
	unregister_signals();
	if (!cmd->is_bg && g_shell.able_termcaps)
		restore_shell(g_shell.prev_term);
	setpgid(getpid(), getpid());
	!cmd->is_bg ? tcsetpgrp(g_shell.pgrp, getpid()) : 0;
	handle_redirections(cmd->redir, 0);
	if (execve(file, cmd->args, env) == -1)
		exit(EXIT_FAILURE);
	exit(0);
}
