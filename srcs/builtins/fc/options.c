/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 17:22:29 by lubenard          #+#    #+#             */
/*   Updated: 2020/01/17 18:06:42 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	fc_parse_option_l(t_cmd *cmd, int *i, int j, t_fc_vars *fc)
{
	if (cmd->args[*i][j] == 'l')
		fc->list = 1;
	else
		fc->exec = 1;
}

void	fc_parse_option_n(t_cmd *cmd, int *i, int j, t_fc_vars *fc)
{
	if (cmd->args[*i][j] == 'n')
		fc->rm = 1;
	else
		fc->rv = 1;
}

int		fc_parse_option_e(t_cmd *cmd, int *i, int j, t_fc_vars *fc)
{
	if (j < (int)ft_strlen(cmd->args[*i]) - 1)
	{
		if (!(fc->editor = ft_strnew(ft_strlen(cmd->args[*i]) - j + 1)))
			return (0);
		ft_strcpy(fc->editor, cmd->args[*i] + j + 1);
		return (2);
	}
	else if (cmd->args[*i + 1])
	{
		if (!(fc->editor = ft_strdup(cmd->args[*i + 1])))
			return (0);
		return (2);
	}
	else
	{
		ft_putendl_fd("42sh: fc: -e: option requires an argument", 2);
		return (-1);
	}
}
