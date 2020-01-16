/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 17:22:29 by lubenard          #+#    #+#             */
/*   Updated: 2020/01/16 17:41:52 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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
