/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 01:34:27 by pcharrie          #+#    #+#             */
/*   Updated: 2020/01/17 18:07:37 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include "utils.h"
#include "shell.h"
#include "libft.h"
#include "variables.h"
#include "builtins.h"
#include "opt.h"

int			fc_parse_options_conditions(t_cmd *cmd, int *i, int j,
t_fc_vars *fc)
{
	while (cmd->args[*i][++j])
	{
		if (cmd->args[*i][j] == 'e')
			return (fc_parse_option_e(cmd, i, j, fc));
		else if (cmd->args[*i][j] == 's')
		{
			fc->exec = 1;
			if (cmd->args[*i + 1] && !ft_isnumeric(cmd->args[*i + 1]))
			{
				fc->s_cmd = ft_strdup(cmd->args[*i + 1]);
				(*i)++;
				return (2);
			}
		}
		else if (cmd->args[*i][j] == 'l' || cmd->args[*i][j] == 's')
			fc_parse_option_l(cmd, i, j, fc);
		else if (cmd->args[*i][j] == 'n' || cmd->args[*i][j] == 'r')
			fc_parse_option_n(cmd, i, j, fc);
		else
		{
			ft_dprintf(2, "42sh: fc: -%c: invalid option\n", cmd->args[*i][j]);
			return (-1);
		}
	}
	return (2);
}

int			fc_parse_options(t_cmd *cmd, t_fc_vars *fc)
{
	int i;
	int j;
	int ret_code;

	i = 0;
	while (++i < cmd->argc)
	{
		if (ft_strlen(cmd->args[i]) > 1 && cmd->args[i][0] == '-'
		&& !ft_isnumeric(cmd->args[i]))
		{
			j = 0;
			if ((ret_code = fc_parse_options_conditions(cmd, &i, j, fc)) != 2)
				return (ret_code);
		}
		else
			break ;
	}
	fc->i = i;
	return (1);
}

static void	fc_fix_range(t_fc_vars *fc)
{
	int hist_size;

	hist_size = g_shell.history.size - 1;
	if (fc->exec)
	{
		if (fc->from == -1)
			fc->from = hist_size;
		fc->to = fc->from;
	}
	else
	{
		if (fc->from < 0)
		{
			fc->to = hist_size;
			fc->from = fc->to + fc->from;
		}
	}
}

int			fc_parse_range(t_cmd *cmd, t_fc_vars *fc)
{
	if (cmd->args[fc->i])
	{
		if (!ft_isnumeric(cmd->args[fc->i]))
		{
			ft_putendl_fd("42sh: fc: history specification out of range", 2);
			return (0);
		}
		fc->from_a = ft_atoi(cmd->args[fc->i++]);
	}
	if (cmd->args[fc->i])
	{
		if (!ft_isnumeric(cmd->args[fc->i]))
		{
			ft_putendl_fd("42sh: fc: history specification out of range", 2);
			return (0);
		}
		fc->to_a = ft_atoi(cmd->args[fc->i++]);
	}
	fc_fix_range(fc);
	return (1);
}
