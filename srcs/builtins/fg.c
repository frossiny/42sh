/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 16:51:40 by lubenard          #+#    #+#             */
/*   Updated: 2019/12/06 17:55:11 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "builtins.h"
#include "jobcontrol.h"
#include "libft.h"
#include "opt.h"
#include "signal.h"
# include <stdio.h>

/*int		job_wait(int )
{
	

	return (0);
}*/

int		change_grp(t_shell *shell, int converted, int cont)
{
	t_jobs_lst	*searched;

	//signal(SIGTTOU, SIG_IGN);
	searched = job_search(shell, converted);
	//printf("searched->pid = %d, STDERR_FILENO = %d\n", searched->pid, STDERR_FILENO);
	if (tcsetpgrp(STDIN_FILENO, searched->pid) < 0)
	{
		perror("Fail to set put pid in foreground");
		return (EXIT_FAILURE);
	}
	//printf("Je suis la\n");
	ft_printf("%s\n", searched->command);
	/* Send the job a continue signal, if necessary.  */
	if (cont)
	{
		tcsetattr(STDERR_FILENO, TCSADRAIN, &shell->prev_term); //causing bug in termcaps when uncommented
		if (kill(-searched->pid, SIGCONT) < 0)
			return (EXIT_FAILURE);
	}
	if (tcsetpgrp(0, shell->pid) < 0)
	{
		perror("Failed to put the shell in foreground");
		return (EXIT_FAILURE);
	}
	/* Restore the shell's terminal modes.  */
	if (tcgetattr(STDERR_FILENO, &shell->prev_term) < 0)
		perror("Error 1");
	if (tcsetattr(STDERR_FILENO, TCSADRAIN, &shell->prev_term) < 0)
		perror("Error 2");
	job_delete(shell, searched->pid);
	return (EXIT_SUCCESS);
}

int		handle_options_fg(t_shell *shell, t_cmd *cmd)
{
	int converted;

	if (cmd->args[1] && cmd->args[1][0] == '%')
		converted = job_percent(cmd->args[1], "fg");
	else if (cmd->args[1])
		converted = ft_atoi(cmd->args[1]);
	else
		converted = shell->jobs.plus->job_number;
	if (!converted)
		return (1);
	return (change_grp(shell, converted, 1));
}

int		b_fg(t_cmd *cmd, t_shell *shell)
{
	t_options	*opts;
	int			ret_code;

	ret_code = 0;
	opts = opt_parse(cmd, "", "fg");
	if (opts->ret != 0)
		(opts->ret == -1 ? ft_putendl_fd("fg: usage: fg [job_spec]",
		2) : 0);
	else
	{
		if (!shell->jobs.lst && !(cmd->argc - opts->last))
			ft_putendl_fd("42sh: fg: current: no such job", 2);
		else if (!shell->jobs.lst && (cmd->argc - opts->last))
			ft_dprintf(2, "42sh: fg: %s: no such job\n", cmd->args[1]);
		else
			ret_code = handle_options_fg(shell, cmd);
	}
	opt_free(opts);
	return (ret_code);
}
