/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 12:10:28 by lubenard          #+#    #+#             */
/*   Updated: 2020/02/03 19:19:20 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs.h"
#include "shell.h"
#include "jobcontrol.h"

int		job_check_valid_number(t_shell *shell, t_cmd *cmd, int j)
{
	if (!ft_atoi(cmd->args[j])
	|| ft_atoi(cmd->args[j]) > (int)shell->jobs.len)
	{
		ft_dprintf(2, "42sh: jobs: %s: no such job\n", cmd->args[j]);
		return (0);
	}
	return (1);
}

int		handle_job_percent_error(char *builtin, char *extract_char,
int *number)
{
	ft_dprintf(2, "42sh: %s: %s: ambiguous job spec\n", builtin,
		extract_char);
	*number = -1;
	return (0);
}

int		handle_job_percent_alpha(char *args, char *builtin)
{
	int			number;
	char		*extract_char;
	t_jobs_lst	*jobs;
	int			occurence;

	number = 0;
	occurence = 0;
	jobs = g_shell.jobs.lst;
	extract_char = (args[1] == '?') ? ft_strsub(args, 2, ft_strlen(args))
	: ft_strsub(args, 1, ft_strlen(args));
	while (jobs)
	{
		if (occurence > 0 || (args[1] == '?' && !args[2]))
			return (handle_job_percent_error(builtin, extract_char, &number));
		if ((args[1] != '?'
		&& !ft_strncmp(jobs->command, extract_char, ft_strlen(extract_char)))
		|| (args[1] == '?' && ft_strstr(jobs->command, extract_char)))
		{
			number = jobs->job_number;
			occurence++;
		}
		jobs = jobs->next;
	}
	ft_strdel(&extract_char);
	return (number);
}

int		job_percent(char *args, char *builtin)
{
	char	*extracted_number;
	int		job_number;

	if (!args[1] || args[1] == '+' || args[1] == '%')
		job_number = g_shell.jobs.plus ? g_shell.jobs.plus->job_number : -1;
	else if (args[1] == '-')
		job_number = g_shell.jobs.minus ? g_shell.jobs.minus->job_number : -1;
	else if (ft_isalpha(args[1]) || args[1] == '?')
		job_number = handle_job_percent_alpha(args, builtin);
	else
	{
		extracted_number = ft_strsub(args, 1, ft_strlen(args));
		job_number = ft_atoi(extracted_number);
		ft_strdel(&extracted_number);
	}
	if (job_number == -1 || !job_search(&g_shell, job_number) \
		|| !job_number)
	{
		ft_dprintf(2, "42sh: %s: %s: no such job\n", builtin, args);
		return (0);
	}
	return (job_number);
}

int		*init_array(t_cmd *cmd, int *i, int *k, int *j)
{
	int *ret;

	*i = 1;
	*k = 0;
	while (cmd->args[*i] && cmd->args[*i][0] == '-')
		(*i)++;
	if (!(ret = malloc(sizeof(int) * (cmd->argc - *i))))
		return (0);
	*j = *i;
	return (ret);
}
