/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:05:36 by lubenard          #+#    #+#             */
/*   Updated: 2019/11/19 18:56:22 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "libft.h"
#include "opt.h"
# include <stdio.h>

int		print_jobs(t_shell *shell, t_options *opts)
{
	t_jobs_lst		*jobs;
	int				options[2];
	t_opt			*tmp_opts;

	tmp_opts = opts->opts;
	jobs = shell->jobs->lst;
	while (opts->opts)
	{
		if (!ft_strcmp(opts->opts->opt, "l"))
			options[0] = 1;
		else if (!ft_strcmp(opts->opts->opt, "p"))
			options[1] = 1;
		opts->opts = opts->opts->next;
	}
	opts->opts = tmp_opts;
	while (jobs)
	{
		if (options[1] == 1)
			ft_printf("%d\n", jobs->pid);
		else
			ft_printf("[%d] %d\n", jobs->job_number, jobs->pid);
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
		(opts->ret == -1 ? ft_putendl_fd("Usage: jobs [-l|-p] [job_id...]", 2) : 0);
	else
		print_jobs(shell, opts);
	opt_free(opts);
	return (0);
}
