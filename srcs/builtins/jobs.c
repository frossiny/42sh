/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:05:36 by lubenard          #+#    #+#             */
/*   Updated: 2019/11/25 18:57:01 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "libft.h"
#include "opt.h"
# include <stdio.h>

int		*build_options(t_shell *shell, t_cmd *cmd, int *size)
{
	int i;
	int j;
	int *ret;
	int	k;

	i = 1;
	k = 0;
	while (cmd->args[i] && cmd->args[i][0] == '-')
		i++;
	if (!(ret = malloc(sizeof(int) * (cmd->argc - i))))
		return (0);
	j = i;
	while (cmd->args[j])
	{
		if (cmd->args[j][0] == '%')
		{
			if (!cmd->args[j][1]
			|| cmd->args[j][1] == '+' || cmd->args[j][1] == '%')
				ret[k++] = shell->jobs->plus->job_number;
			else if (cmd->args[j][1] == '-')
				ret[k++] = shell->jobs->minus->job_number;
			else
				ret[k++] = ft_atoi(ft_strsub(cmd->args[j], 1, ft_strlen(cmd->args[j] - 1)));
			printf("Je viens d'enregistrer %d\n", ret[k - 1]);
		}
		else if (!ft_atoi(cmd->args[j])
		|| ft_atoi(cmd->args[j]) >= (int)shell->jobs->index)
		{
			ft_dprintf(2, "bash: jobs: %s: no such job", cmd->args[j]);
			free(ret);
			*size = 0;
			return (0);
		}
		else
			ret[k++] = ft_atoi(cmd->args[j]);
		j++;
	}
	*size = cmd->argc - i;
	return (ret);
}

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
				ft_printf("[%d] %c %d %s %s\n", jobs->job_number, jobs->current,
				jobs->pid, jobs->state, jobs->command);
			else
				ft_printf("[%d] %c %s %s\n", jobs->job_number, jobs->current,
				jobs->state, jobs->command);
		}
		jobs = jobs->next;
	}
	return (0);
}

int		print_jobs(t_shell* shell, t_cmd *cmd, t_options *opts, int options)
{
	int			job_number;
	int			*default_array;
	t_jobs_lst	*tmp_lst;
	int			size;

	job_number = 0;
	if (cmd->argc - opts->last)
	{
		if (!(default_array = build_options(shell, cmd, &size)))
			return (1);
	}
	else
	{
		size = shell->jobs->index - 1;
		tmp_lst = shell->jobs->lst;
		if (!(default_array = malloc(sizeof(int) * shell->jobs->index - 1)))
			return (1);
		while (tmp_lst && job_number != (int)shell->jobs->index)
		{
			default_array[job_number++] = tmp_lst->job_number;
			tmp_lst = tmp_lst->next;
		}
	}
	job_number = 0;
	while (job_number != size)
		print_job(shell, options, default_array[job_number++]);
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
		ft_printf("cmd->argc - opts->last = %d\n", cmd->argc - opts->last);
		print_jobs(shell, cmd, opts, handle_options(opts));
		opt_free(opts);
	}
	return (0);
}
