/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:05:36 by lubenard          #+#    #+#             */
/*   Updated: 2019/12/10 16:24:16 by lubenard         ###   ########.fr       */
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

	jobs = shell->jobs.lst;
	if (!job_number)
		return (0);
	while (jobs)
	{
		if (jobs->job_number == job_number)
		{
			if (options == 1)
				ft_printf("%d\n", jobs->pid);
			else if (options == 2)
				ft_printf("[%d]%c %d %s %s\n", jobs->job_number, jobs->current,
				jobs->pid, jobs->status, jobs->command);
			else
				ft_printf("[%d]%c %s %s\n", jobs->job_number, jobs->current,
				jobs->status, jobs->command);
		}
		jobs = jobs->next;
	}
	return (0);
}

int		print_jobs(t_shell *shell, t_cmd *cmd, t_options *opts, int opti)
{
	int			job_num;
	t_jobs_lst	*display;

	job_num = 1;
	display = shell->jobs.lst;
	if (cmd->argc - opts->last)
	{
		while (cmd->args[job_num])
		{
			if (cmd->args[job_num][0] == '%')
				print_job(shell, opti, job_percent(cmd->args[job_num], "jobs"));
			else if (job_check_valid_number(shell, cmd, job_num))
				print_job(shell, opti, ft_atoi(cmd->args[job_num]));
			job_num++;
		}
	}
	else
	{
		while (display)
		{
			print_job(shell, opti, display->job_number);
			display = display->next;
		}
	}
	return (0);
}

int		b_jobs(t_cmd *cmd, t_shell *shell)
{
	t_options	*opts;

	if (shell->jobs.lst)
	{
		opts = opt_parse(cmd, "lp", "jobs");
		if (opts->ret != 0)
			(opts->ret == -1 ? ft_putendl_fd("Usage: jobs [-l|-p] [job_id...]"
			, 2) : 0);
		else
			print_jobs(shell, cmd, opts, handle_options(opts));
		opt_free(opts);
	}
	return (0);
}
