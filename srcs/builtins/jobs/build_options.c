/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 12:10:28 by lubenard          #+#    #+#             */
/*   Updated: 2019/11/26 14:23:37 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs.h"
#include "shell.h"

int		job_check_valid_number(t_shell *shell, t_cmd *cmd, int *ret, int j)
{
	if (!ft_atoi(cmd->args[j])
	|| ft_atoi(cmd->args[j]) >= (int)shell->jobs->index)
	{
		ft_dprintf(2, "42sh: jobs: %s: no such job", cmd->args[j]);
		free(ret);
		return (0);
	}
	return (1);
}

int		handle_job_percent(char *args, int **ret, int *k)
{
	char	*extracted_number;

	if (!args[1] || args[1] == '+' || args[1] == '%')
		(*ret)[(*k)++] = g_shell.jobs->plus->job_number;
	else if (args[1] == '-')
		(*ret)[(*k)++] = g_shell.jobs->minus->job_number;
	else
	{
		extracted_number = ft_strsub(args, 1, ft_strlen(args));
		(*ret)[(*k)++] = ft_atoi(extracted_number);
		ft_strdel(&extracted_number);
	}
	if ((*ret)[(*k) - 1] >= (int)g_shell.jobs->index)
	{
		ft_dprintf(2, "42sh: jobs: %%%d: no such job\n", (*ret)[(*k) - 1]);
		return (0);
	}
	return (1);
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

int		*build_options(t_shell *shell, t_cmd *cmd, int *size)
{
	int i;
	int j;
	int *ret;
	int k;

	ret = init_array(cmd, &i, &k, &j);
	while (cmd->args[j])
	{
		if (cmd->args[j][0] == '%')
		{
			if (!(handle_job_percent(cmd->args[j], &ret, &k)))
			{
				free(ret);
				return (0);
			}
		}
		else if (!job_check_valid_number(shell, cmd, ret, j))
			return (0);
		else
			ret[k++] = ft_atoi(cmd->args[j]);
		j++;
	}
	*size = cmd->argc - i;
	return (ret);
}

int		*get_default_array(t_shell *shell, int *size)
{
	int			*array;
	t_jobs_lst	*tmp_lst;
	int			job_number;

	job_number = 0;
	*size = shell->jobs->index - 1;
	tmp_lst = shell->jobs->lst;
	if (!(array = malloc(sizeof(int) * (shell->jobs->index - 1))))
		return (0);
	while (tmp_lst && job_number != (int)shell->jobs->index)
	{
		array[job_number++] = tmp_lst->job_number;
		tmp_lst = tmp_lst->next;
	}
	return (array);
}
