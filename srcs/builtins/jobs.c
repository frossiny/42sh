/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:05:36 by lubenard          #+#    #+#             */
/*   Updated: 2019/11/21 18:44:14 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "libft.h"
#include "opt.h"
# include <stdio.h>

char	*reconstruct_command(t_anode *command)
{
	int		i;
	int		e;
	char	*ret;
	char	**tab;

	tab = command->cmd->args;
	i = 0;
	e = 0;
	while (tab[e])
		i += ft_strlen(tab[e++]);
	if (!(ret = ft_strnew(i)))
		return (NULL);
	e = 0;
	while (tab[e])
		ft_strcat(ret, tab[e]);
		e++;
	return (ret);
}

int		*handle_options(t_options *opts)
{
	t_opt			*tmp_opts;
	int				*options;

	tmp_opts = opts->opts;
	if (!(options = malloc(sizeof(int) * 2)))
		return (0);
	options[0] = 0;
	options[1] = 0;
	while (opts->opts)
	{
		if (!ft_strcmp(opts->opts->opt, "l"))
			options[0] = 1;
		else if (!ft_strcmp(opts->opts->opt, "p"))
			options[1] = 1;
		opts->opts = opts->opts->next;
	}
	opts->opts = tmp_opts;
	return (options);
}

int		print_jobs(t_shell *shell, int *options)
{
	t_jobs_lst		*jobs;

	jobs = shell->jobs->lst;
	while (jobs)
	{
		if (options[1] == 1)
			ft_printf("%d\n", jobs->pid);
		else if (options[0] == 1)
			ft_printf("[%d] %c %d %s %s\n", jobs->job_number, jobs->current,
			jobs->pid, jobs->state, "Okay");//reconstruct_command(jobs->command));
		else
			ft_printf("[%d] %c %s %s\n", jobs->job_number, jobs->current,
			jobs->state, "Okay");//reconstruct_command(jobs->command));
		jobs = jobs->next;
	}
	return (0);
}

int		b_jobs(t_cmd *cmd, t_shell *shell)
{
	t_options	*opts;

	(void)shell;
	if (shell->jobs)
	{
		opts = opt_parse(cmd, "lp", "jobs");
		if (opts->ret != 0)
			(opts->ret == -1 ? ft_putendl_fd("Usage: jobs [-l|-p] [job_id...]"
			, 2) : 0);
		else
			print_jobs(shell, handle_options(opts));
		opt_free(opts);
	}
	return (0);
}
