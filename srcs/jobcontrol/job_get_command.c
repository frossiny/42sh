/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_get_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 10:52:06 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/28 11:04:05 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobcontrol.h"

char	*job_get_command(t_cmd *cmd)
{
	int		i;
	int		e;
	char	*ret;

	if (!cmd || !cmd->args)
		return (NULL);
	i = 0;
	e = 0;
	while (cmd->args[e])
		i += ft_strlen(cmd->args[e++]) + 1;
	if (!(ret = ft_strnew(i)))
		return (NULL);
	e = 0;
	while (cmd->args[e])
	{
		ft_strcat(ret, cmd->args[e++]);
		ft_strcat(ret, " ");
	}
	return (ret);
}
