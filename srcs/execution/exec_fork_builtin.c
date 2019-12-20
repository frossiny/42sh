/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fork_builtin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 10:35:21 by frossiny          #+#    #+#             */
/*   Updated: 2019/12/20 15:07:57 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "builtins.h"
#include "execution.h"
#include "jobcontrol.h"
#include "utils.h"

int		exec_fork_builtin(t_cmd *cmd)
{
	t_builtin	builtin;
	int			status;

	if (!(builtin = get_builtin(cmd->exe->content)).func)
		return (-1);
	if (!get_here_doc(cmd->redir, &g_shell))
		return (EXIT_FAILURE);
	if ((g_child = fork()) > 0 && cmd->is_bg)
	{
		ft_printf("cmd->is_bg %d\n", cmd->is_bg);
		job_new(cmd, g_child);
	}
	if (!g_child)
	{
		unregister_signals();
		setpgid(0, 0);
		handle_redirections(cmd->redir, 0);
		status = builtin.func(cmd, &g_shell);
		var_destroy(&(cmd->tenv));
		u_free_shell();
		exit(status);
	}
	close_here_docs(cmd->redir);
	if (g_child == -1)
		return (g_child = 0);
	waitpid(g_child, &status, WNOHANG);
	g_child = 0;
	return (0);
}
