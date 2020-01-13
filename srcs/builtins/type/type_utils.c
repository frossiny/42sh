/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 14:20:57 by vsaltel           #+#    #+#             */
/*   Updated: 2020/01/09 14:51:18 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <dirent.h>
#include "libft.h"

char		*check_path(char *path, char *arg)
{
	DIR				*dirp;
	struct dirent	*dirc;
	char			*var;

	if ((dirp = opendir(path)) == NULL)
		return (NULL);
	while ((dirc = readdir(dirp)) != NULL)
	{
		if (ft_strcmp(arg, dirc->d_name) == 0)
		{
			var = ft_strpathfile(path, dirc->d_name);
			closedir(dirp);
			return (var);
		}
	}
	closedir(dirp);
	return (NULL);
}

int			is_executable(char *arg)
{
	struct stat	pstat;
	int			res;

	if (!arg && !access(arg, F_OK) && access(arg, X_OK))
		return (0);
	res = stat(arg, &pstat);
	if (!res && S_ISREG(pstat.st_mode))
		return (1);
	return (0);
}