/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_get_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 16:22:21 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/22 17:12:46 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "execution.h"
#include "utils.h"

char	*exec_get_file(t_cmd *cmd, int *errno, int verbose)
{
	int		ret;
	char	*file;

	if (!cmd)
		return (NULL);
	if (!(file = get_exe(&g_shell, cmd->exe->content, verbose)))
	{
		errno ? *errno = 127 : 0;
		return (NULL);
	}
	if ((ret = can_execute(cmd->exe->content, &g_shell)))
	{
		errno ? *errno = 126 : 0;
		free(file);
		return (NULL);
	}
	return (file);
}
