/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 14:23:23 by vsaltel           #+#    #+#             */
/*   Updated: 2020/01/20 15:19:35 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "hashtable.h"
#include "libft.h"
#include "builtins.h"

int			type_path(char *arg, size_t *find)
{
	if (arg[0] && ((arg[0] == '/')
				|| (arg[0] == '.' && arg[1] && arg[1] == '/')))
		if (is_executable(arg))
		{
			ft_printf("%s is %s\n", arg, arg);
			return (++(*find));
		}
	return (0);
}

int			type_env_path(char *arg, size_t *find, t_var *vars)
{
	char	*path;
	char	*res;
	char	**tab;
	size_t	i;

	if (!(path = var_get_value(vars, "PATH")))
		return (0);
	tab = ft_strsplit(path, ':');
	free(path);
	i = -1;
	while (tab[++i])
		if ((res = check_path(tab[i], arg)))
		{
			if (is_executable(res))
			{
				ft_printf("%s is %s\n", arg, res);
				free(res);
				ft_strddel(&tab);
				return (++(*find));
			}
			free(res);
		}
	ft_strddel(&tab);
	return (0);
}

int			type_hashtable(char *arg, size_t *find)
{
	char	*var;

	if (ht_exists(&g_shell, arg))
	{
		var = ht_get(&g_shell, arg);
		ft_printf("%s is hashed (%s)\n", arg, var);
		free(var);
		return (++(*find));
	}
	return (0);
}

int			type_builtin(char *arg, size_t *find)
{
	size_t	i;

	i = 0;
	while (g_builtins[i].name)
	{
		if (ft_strcmp(arg, g_builtins[i].name) == 0)
		{
			ft_printf("%s is a shell builtin\n", arg);
			return (++(*find));
		}
		i++;
	}
	return (0);
}

int			type_alias(char *arg, size_t *find, t_alias *alias)
{
	while (alias)
	{
		if (!ft_strcmp(arg, alias->key))
		{
			ft_printf("%s is aliased to `%s'\n", arg, alias->value);
			return (++(*find));
		}
		alias = alias->next;
	}
	return (0);
}
