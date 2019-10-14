/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 14:41:24 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/14 15:15:17 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "shell.h"
#include "utils.h"

static void	update_env(t_env **env)
{
	char	*tmp;
	t_env	*pwd;
	t_env	*oldpwd;

	tmp = getcwd(NULL, 0);
	pwd = get_enve(*env, "PWD");
	if (pwd)
	{
		if (!(oldpwd = get_enve(*env, "OLDPWD")))
			oldpwd = new_envl(env, "OLDPWD", pwd->value, 0);
		else
		{
			free(oldpwd->value);
			if (!(oldpwd->value = ft_strdup(pwd->value)))
				exit(1);
		}
		free(pwd->value);
		if (!(pwd->value = ft_strdup(tmp)))
			exit(1);
	}
	else
		pwd = new_envl(env, "PWD", tmp, 0);
	free(tmp);
}

static char	*build_path(char *arg)
{
	char	*tmp;
	char	*path;

	path = NULL;
	if (arg[0] == '/')
		return (ft_strdup(arg));
	tmp = getcwd(NULL, 0);
	path = ft_strjoint(tmp, "/", arg);
	free(tmp);
	return (path);
}

static char	*get_oldpwd(t_env *env)
{
	t_env	*pwd;

	if (!(pwd = get_enve(env, "OLDPWD")))
		return (ft_strdup(""));
	return (ft_strdup(pwd->value));
}

static char	*get_newdir(int argc, char **argv, t_env *env)
{
	char	*path;
	t_env	*home;

	path = NULL;
	if (argc == 1 && !(home = get_enve(env, "HOME")))
	{
		write(2, "cd: HOME not set\n", 17);
		return (NULL);
	}
	else if (argc == 1 && home)
		path = ft_strdup(home->value);
	else if (argc == 2 && ft_strcmp(argv[1], "-") == 0)
		path = get_oldpwd(env);
	else
		path = build_path(argv[1]);
	if (!path || !cd_exists(path, argv[1])
							|| cd_is_dir(path, argv[1]) < 0)
	{
		path ? free(path) : 0;
		return (NULL);
	}
	return (path);
}

int			b_cd(t_cmd *cmd, t_shell *shell)
{
	char	*newdir;
	int		ret;

	if (!(newdir = get_newdir(cmd->argc, cmd->args, shell->env)))
		return (1);
	ret = chdir(newdir);
	update_env(&(shell->env));
	free(newdir);
	return (ret);
}
