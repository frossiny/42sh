/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_can_put.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 16:11:18 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/20 08:48:17 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "shell.h"
#include "execution.h"

int		ht_can_put(char *cmd)
{
	struct stat	stats;
	char		*file;

	if (!(file = get_exe(&g_shell, cmd, 0)))
		return (0);
	if (access(file, X_OK))
	{
		free(file);
		return (0);
	}
	if ((stat(file, &stats) == -1) || !S_ISREG(stats.st_mode))
	{
		free(file);
		return (0);
	}
	free(file);
	return (1);
}
