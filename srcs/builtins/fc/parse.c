/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 01:34:27 by pcharrie          #+#    #+#             */
/*   Updated: 2019/11/19 04:35:03 by pcharrie         ###   ########.fr       */
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

int			fc_parse_options(t_cmd *cmd, t_fc_vars *fc)
{
	int i;
	int j;

	i = 0;
	while (++i < cmd->argc)
	{
		if (ft_strlen(cmd->args[i]) > 1 && cmd->args[i][0] == '-' && !ft_isnumeric(cmd->args[i]))
		{
			j = 0;
			while (cmd->args[i][++j])
			{
				if (cmd->args[i][j] == 'e')
				{
					if (j < ft_strlen(cmd->args[i]) - 1)
					{
						if (!(fc->editor = ft_strnew(ft_strlen(cmd->args[i]) - j + 1)))
							return (0);
						ft_strcpy(fc->editor, cmd->args[i] + j + 1);
					}
					else if (cmd->args[i + 1])
					{
						if (!(fc->editor = ft_strdup(cmd->args[i + 1])))
							return (0);
					}
					else
					{
						ft_putendl_fd("42sh: fc: -e: option requires an argument", 2);
						return (-1);
					}
					break ;
				}
				else if (cmd->args[i][j] == 's')
				{
					fc->exec = 1;
					if (cmd->args[i + 1] && !ft_isnumeric(cmd->args[i + 1]))
					{
						fc->s_cmd = ft_strdup(cmd->args[i + 1]);
						++i;
						break ;
					}
				}
				else if (cmd->args[i][j] == 'l' || cmd->args[i][j] == 's')
					cmd->args[i][j] == 'l' ? (fc->list = 1) : (fc->exec = 1);
				else if (cmd->args[i][j] == 'n' || cmd->args[i][j] == 'r')
					cmd->args[i][j] == 'n' ? (fc->rm = 1) : (fc->rv = 1);
				else
				{
					ft_dprintf(2, "42sh: fc: -%c: invalid option\n", cmd->args[i][j]);
					return (-1);
				}
			}
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

	hist_size = fc_histo_lst_size();
	if (fc->exec)
	{
		if (fc->from == -1)
			fc->from = fc_histo_lst_size();
		fc->to = fc->from;
	}
	else
	{
		if (fc->from < 1)
		{
			if (fc_get_mode(fc) == 2)
			{
				fc->from = (hist_size - 15 < 1 ? 1 : hist_size - 15);
				fc->to = hist_size;
			}
			else
				fc->from = hist_size;
		}
		if (fc->to > -1 && fc->to < fc->from)
		{
			hist_size = fc->to;
			fc->to = fc->from;
			fc->from = hist_size;
			fc->rv = 1;
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
		fc->from = ft_atoi(cmd->args[fc->i++]);
	}
	if (cmd->args[fc->i])
	{
		if (!ft_isnumeric(cmd->args[fc->i]))
		{
			ft_putendl_fd("42sh: fc: history specification out of range", 2);
			return (0);
		}
		fc->to = ft_atoi(cmd->args[fc->i++]);
	}
	fc_fix_range(fc);
	return (1);
}
