/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 11:53:12 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/28 19:48:33 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "lexer.h"
#include "ast.h"
#include "alias.h"
#include "termcaps.h"
#include "hashtable.h"
#include "jobcontrol.h"

static int	check_arg(t_cmd *cmd)
{
	if (!ft_strisdigit(cmd->args[1]))
	{
		write(2, "exit: Numeric argument required\n", 32);
		return (0);
	}
	return (1);
}

int			b_exit(t_cmd *cmd, t_shell *shell)
{
	int		ret;

	if (cmd->argc > 2)
	{
		write(2, "exit: Too many arguments\n", 25);
		return (1);
	}
	ret = g_return;
	if (cmd->argc == 2 && !check_arg(cmd))
		ret = 1;
	else if (cmd->argc == 2)
		ret = ft_atoi(cmd->args[1]);
	(void)shell;
	if (!g_shell.stopped_jobs && !job_can_exit())
	{
		g_shell.stopped_jobs = 1;
		g_shell.pid == getpid() ? \
			ft_dprintf(2, "There are stopped jobs.\n") : 0;
		return (g_shell.pid == getpid());
	}
	u_free_shell(g_shell.pid == getpid());
	exit(ret);
	return (ret);
}
