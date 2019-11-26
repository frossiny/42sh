/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 17:27:04 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/26 18:47:26 by lubenard         ###   ########.fr       */
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

static char	*get_exe_path(t_shell *shell, char *name)
{
	t_var			*path;
	char			**dirs;
	size_t			i;
	char			*file;
	static size_t	is_called_twice = 0;

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
		if (is_called_twice)
			is_called_twice = 0;
		else if (!is_called_twice)
		{
			ht_put(shell, name, file, 1);
			is_called_twice = 1;
		}
		return (file);
	}
	ft_strdel(&file);
	return (NULL);
}

char		*get_exe(t_shell *shell, char *name, int verbose)
{
	char		*file;
	struct stat	stats;

	if (!name || name[0] == '\0')
		return (ft_strdup(""));
	file = NULL;
	if (name[0] == '/')
		return (handle_absolute(name, verbose));
	else if (is_relative_path(name))
		return (handle_relative(name, verbose));
	file = get_exe_path(shell, name);
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

	tmp = get_exe(shell, name, verbose);
	ret = tmp != NULL;
	free(tmp);
	return (ret);
}
