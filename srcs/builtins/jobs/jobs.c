/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:05:36 by lubenard          #+#    #+#             */
/*   Updated: 2019/11/27 14:14:06 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "libft.h"
#include "opt.h"
#include "builtins.h"

int		handle_options(t_options *opts)
{
	t_opt	*tmp_opts;
	int		option;

	option = 0;
	tmp_opts = opts->opts;
	while (tmp_opts)
	{
		if (!ft_strcmp(tmp_opts->opt, "l"))
			option = 1;
		else if (!ft_strcmp(tmp_opts->opt, "p"))
			option = 2;
		tmp_opts = tmp_opts->next;
	}
	return (option);
}

int		print_job(t_shell *shell, int options, int job_number)
{
	t_jobs_lst		*jobs;

	jobs = shell->jobs->lst;
	while (jobs)
	{
		if (jobs->job_number == job_number)
		{
			if (options == 1)
				ft_printf("%d\n", jobs->pid);
			else if (options == 2)
				ft_printf("[%d]%c %d %s %s\n", jobs->job_number, jobs->current,
				jobs->pid, jobs->state, jobs->command);
			else
				ft_printf("[%d]%c %s %s\n", jobs->job_number, jobs->current,
				jobs->state, jobs->command);
		}
		jobs = jobs->next;
	}
	return (0);
}

int		print_jobs(t_shell *shell, t_cmd *cmd, t_options *opts, int options)
{
	int			job_number;
	int			*default_array;
	int			size;

	job_number = 0;
	default_array = (cmd->argc - opts->last) ? build_options(shell, cmd, &size)
	: get_default_array(shell, &size);
	if (!default_array)
		return (1);
	while (job_number != size)
		print_job(shell, options, default_array[job_number++]);
	free(default_array);
	return (0);
}

int		b_jobs(t_cmd *cmd, t_shell *shell)
{
	t_options	*opts;

	if (shell->jobs)
	{
		opts = opt_parse(cmd, "lp", "jobs");
		if (opts->ret != 0)
			(opts->ret == -1 ? ft_putendl_fd("Usage: jobs [-l|-p] [job_id...]"
			, 2) : 0);
		print_jobs(shell, cmd, opts, handle_options(opts));
		opt_free(opts);
	}
	return (0);
}
