/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 12:10:28 by lubenard          #+#    #+#             */
/*   Updated: 2019/11/28 15:11:54 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs.h"
#include "shell.h"

int		job_check_valid_number(t_shell *shell, t_cmd *cmd, int j)
{
	if (!ft_atoi(cmd->args[j])
	|| ft_atoi(cmd->args[j]) >= (int)shell->jobs.index)
	{
		ft_dprintf(2, "42sh: jobs: %s: no such job\n", cmd->args[j]);
		return (0);
	}
	return (1);
}

int		handle_job_percent_alpha(char *args)
{
	int			number;
	char		*extracted_char;
	t_jobs_lst	*jobs;
	int			occurence;

	number = 0;
	occurence = 0;
	jobs = g_shell.jobs.lst;
	if (args[1] == '?')
		extracted_char = ft_strsub(args, 2, ft_strlen(args));
	else
		extracted_char = ft_strsub(args, 1, ft_strlen(args));
	while (jobs)
	{
		if (occurence > 0 || (args[1] == '?' && !args[2]))
		{
			ft_dprintf(2, "42sh: jobs: %s: ambiguous job spec\n",
			extracted_char);
			number = -1;
			break ;
		}
		if ((args[1] != '?' && !ft_strncmp(jobs->command, extracted_char, ft_strlen(extracted_char))) || (args[1] == '?' && ft_strstr(jobs->command, extracted_char)))
		{
			number = jobs->job_number;
			occurence++;
		}
		jobs = jobs->next;
	}
	ft_strdel(&extracted_char);
	return (number);
}

int		handle_job_percent(char *args)
{
	char	*extracted_number;
	int		converted_number;

	if (!args[1] || args[1] == '+' || args[1] == '%')
		converted_number = g_shell.jobs.plus->job_number;
	else if (args[1] == '-')
		converted_number = g_shell.jobs.minus->job_number;
	else if (ft_isalpha(args[1]) || args[1] == '?')
		converted_number = handle_job_percent_alpha(args);
	else
	{
		extracted_number = ft_strsub(args, 1, ft_strlen(args));
		converted_number = ft_atoi(extracted_number);
		ft_strdel(&extracted_number);
	}
	if (converted_number == -1)
		return (0);
	if (converted_number >= (int)g_shell.jobs.index || !converted_number)
	{
		ft_dprintf(2, "42sh: jobs: %s: no such job\n", args);
		return (0);
	}
	return (converted_number);
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
