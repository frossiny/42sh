/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_get_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 16:22:21 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/17 16:22:45 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "execution.h"
#include "utils.h"

char	*exec_get_file(t_cmd *cmd, int *errno)
{
	int		ret;
	char	*file;

	if (!(file = get_exe(&g_shell, cmd->exe->content, 1)))
	{
		*errno = 127;
		return (NULL);
	}
	if ((ret = can_execute(cmd->exe->content, &g_shell)))
	{
		*errno = 126;
		free(file);
		return (NULL);
	}
	return (file);
}
