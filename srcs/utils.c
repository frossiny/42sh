/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 12:46:01 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/17 16:18:51 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/stat.h>
#include "libft.h"
#include "shell.h"
#include "execution.h"
#include "utils.h"

char	*format_path_exe(char *dir, char *file)
{
	char	*path;

	path = NULL;
	if (dir[ft_strlen(dir) - 1] != '/')
		path = ft_strjoint(dir, "/", file);
	else
		path = ft_strjoin(dir, file);
	return (path);
}

int		is_local_exe(char *name)
{
	if (ft_strlen(name) > 1 && name[0] == '.' && name[1] == '/')
		return (1);
	if (ft_strlen(name) > 2 && name[0] == '.' && name[1] == '.'
													&& name[2] == '/')
		return (1);
	return (0);
}

int		is_relative_path(char *name)
{
	while (*name)
	{
		if (*name == '/')
			return (1);
		name++;
	}
	return (0);
}

int		cd_is_dir(char *file, char *name)
{
	struct stat stats;

	if (stat(file, &stats) == -1)
		return (0);
	if (!S_ISDIR(stats.st_mode))
	{
		ft_dprintf(2, "42sh: not a directory: %s\n", name);
		return (-1);
	}
	return (1);
}

int		can_execute(char *cmd, t_shell *shell)
{
	char		*file;
	struct stat	stats;

	if (!(file = get_exe(shell, cmd, 1)))
		return (127);
	if (ft_strequ(file, "") || access(file, X_OK))
	{
		permission_denied(file);
		free(file);
		return (126);
	}
	else if ((stat(file, &stats) == -1) || !S_ISREG(stats.st_mode))
	{
		free(file);
		return (is_directory_err(cmd));
	}
	free(file);
	return (0);
}
