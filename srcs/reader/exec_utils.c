/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 17:27:04 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/14 18:42:23 by frossiny         ###   ########.fr       */
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
	t_var		*path;
	char		**dirs;
	size_t		i;
	char		*file;

	if ((file = ht_get(shell, name)))
		return (file);
	if (!(path = var_get(shell->vars, "PATH")) || !ft_strlen(path->value))
		return (NULL);
	i = -1;
	dirs = ft_strsplit(path->value, ':');
	while (dirs && dirs[++i])
	{
		if (access(file = format_path_exe(dirs[i], name), F_OK) == 0)
			break ;
		ft_strdel(&file);
	}
	ft_strddel(&dirs);
	if (file && access(file, F_OK) == 0)
	{
		ht_put(shell, name, file);
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
