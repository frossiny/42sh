/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child_fork.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 11:08:12 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/22 17:06:36 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "execution.h"
#include "utils.h"
#include "ast.h"

int		exec_child_fork(t_cmd *cmd, char **env)
{
	int		error;
	char	*file;

	unregister_signals();
	if (!cmd->is_bg && g_shell.able_termcaps)
		restore_shell(g_shell.prev_term);
	setpgid(getpid(), getpid());
	!cmd->is_bg ? tcsetpgrp(g_shell.pgrp, getpid()) : 0;
	handle_redirections(cmd->redir, 0);
	error = EXIT_FAILURE;
	if (!(file = exec_get_file(cmd, &error, 1)) \
		|| execve(file, cmd->args, env) == -1)
	{
		ft_strddel(&env);
		u_free_shell();
		exit(error);
	}
	exit(0);
}
