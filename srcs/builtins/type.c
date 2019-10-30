/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 17:40:24 by vsaltel           #+#    #+#             */
/*   Updated: 2019/10/30 19:02:07 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "hashtable.h"
#include "builtins.h"
#include "libft.h"
#include <dirent.h>

char		*check_path(char *path, char *arg)
{
	DIR				*dirp;
	struct dirent	*dirc;

	if ((dirp = opendir(path)) == NULL)
		return (NULL);
	while ((dirc = readdir(dirp)) != NULL)
	{
		if (ft_strcmp(arg, dirc->d_name) == 0)
			return (ft_strpathfile(path, dirc->d_name));
	}
	return (NULL);
}

int			find_path(char *arg, size_t *find, t_var *vars)
{
	char	*path;
	char	*res;
	char	**tab;
	size_t	i;

	if (!(path = var_get_value(vars, "PATH")))
		return (0);
	tab = ft_strsplit(path, ':');
	i = -1;
	while (tab[++i])
	{
		if ((res = check_path(tab[i], arg)))
		{
			ft_printf("%s is %s\n", arg, res);
			free(res);
			ft_strddel(&tab);
			(*find)++;
			return (1);
		}
	}
	free(path);
	ft_strddel(&tab);
	return (0);
}

int			find_hashtable(char *arg, size_t *find)
{
	if (ht_exists(&g_shell, arg))
	{
		ft_printf("%s is hashed (%s)\n", arg, ht_get(&g_shell, arg));
		(*find)++;
		return (1);
	}
	return (0);
}

int			find_builtin(char *arg, size_t *find)
{
	size_t	i;

	i = 0;
	while (g_builtins[i].name)
	{
		if (ft_strcmp(arg, g_builtins[i].name) == 0)
		{
			(*find)++;
			ft_printf("%s is a shell builtin\n", arg);
			return (1);
		}
		i++;
	}
	return (0);
}

int			b_type(t_cmd *cmd, t_shell *shell)
{
	size_t	i;
	size_t	find;

	find = 0;
	i = 1;
	while (i < cmd->argc)
	{
		if (!find_builtin(cmd->args[i], &find))
			if (!find_hashtable(cmd->args[i], &find))
				if (!find_path(cmd->args[i], &find, shell->vars))
					ft_printf("42sh: type: %s: not found\n", cmd->args[i]);
		i++;
	}
	if (find)
		return (0);
	else
		return (1);
}
