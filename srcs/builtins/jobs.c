/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:05:36 by lubenard          #+#    #+#             */
/*   Updated: 2019/11/19 14:27:42 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "libft.h"
#include "opt.h"
# include <stdio.h>

int		print_jobs(t_shell *shell)
{
	size_t			counter;
	t_jobs			*jobs;

	counter = 1;
	jobs = shell->jobs;
	while (jobs)
	{
		//ft_printf("command = %s\n", jobs->ast->cmd->argv[0]);
		ft_printf("[%zu] command\n", counter++);
		jobs = jobs->next;
	}
	return (0);
}

int		b_jobs(t_cmd *cmd, t_shell *shell)
{
	t_options	*opts;

	(void)shell;
	opts = opt_parse(cmd, "lp", "jobs");
	if (opts->ret != 0)
		(opts->ret == -1 ? ft_putendl_fd("jobs [-l|-p] [job_id...]", 2) : 0);
	else if (cmd->argc == 1)
		print_jobs(shell);
	opt_free(opts);
	return (0);
}
