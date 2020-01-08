/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 17:27:04 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/08 11:35:36 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "libft.h"
#include "shell.h"
#include "utils.h"
#include "hashtable.h"

static char	*handle_absolute(char *name, int verbose)
{
	char	*file;

	file = NULL;
	file = ft_strdup(name);
	if (file && access(file, F_OK) != -1)
	{
		if (access(file, X_OK) == -1)
			verbose ? permission_denied(name) : 0;
		return (file);
	}
	verbose ? inexistant(name) : 0;
	if (file)
		free(file);
	return (NULL);
}

static char	*handle_relative(char *name, int verbose)
{
	char	*tmp;
	char	*file;

	tmp = getcwd(NULL, 0);
	if (!(file = ft_strjoint(tmp, "/", name)))
	{
		free(tmp);
		return (NULL);
	}
	free(tmp);
	if (access(file, F_OK) != -1)
	{
		if (access(file, X_OK) == -1)
			verbose ? permission_denied(name) : 0;
		return (file);
	}
	free(file);
	verbose ? inexistant(name) : 0;
	return (NULL);
}

static char	*get_exe_path(t_shell *shell, char *name, int is_exe)
{
	t_var			*path;
	char			**dirs;
	size_t			i;
	char			*file;

	file = ht_get(shell, name);
	if (!(path = var_get(shell->vars, "PATH")) || ft_strlen(path->value) == 0)
		return (handle_relative(name, 0));
	i = -1;
	dirs = ft_strsplit(path->value, ':');
	while (dirs && dirs[++i])
	{
		ft_strdel(&file);
		if (access(file = format_path_exe(dirs[i], name), F_OK) == 0)
			break ;
	}
	ft_strddel(&dirs);
	if (file && access(file, F_OK) == 0)
	{
		!is_exe ? ht_put(shell, name, file, 1) : 0;
		return (file);
	}
	ft_strdel(&file);
	return (NULL);
}

char		*get_exe(t_shell *shell, char *name, int verbose, int is_exe)
{
	char		*file;
	struct stat	stats;

	if (!name || name[0] == '\0')
	{
		verbose ? not_found(name) : 0;
		return (NULL);
	}
	file = NULL;
	if (name[0] == '/')
		return (handle_absolute(name, verbose));
	else if (is_relative_path(name))
		return (handle_relative(name, verbose));
	file = get_exe_path(shell, name, is_exe);
	if (file && stat(file, &stats) == 0)
		return (file);
	if (file)
		free(file);
	verbose ? not_found(name) : 0;
	return (NULL);
}

int			is_exe(t_shell *shell, char *name, int verbose)
{
	int		ret;
	char	*tmp;

	tmp = get_exe(shell, name, verbose, 1);
	ret = tmp != NULL;
	free(tmp);
	return (ret);
}
