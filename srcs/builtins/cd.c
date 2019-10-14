/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 14:41:24 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/14 18:59:40 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "shell.h"
#include "utils.h"

static void	update_env(t_var **vars)
{
	char	*tmp;
	t_var	*pwd;

	if (!(tmp = getcwd(NULL, 0)))
		return ;
	if ((pwd = var_get(*vars, "PWD")))
		var_set(vars, "OLDPWD", pwd->value, 1);
	var_set(vars, "PWD", tmp, 1);
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

static char	*get_oldpwd(t_var *vars)
{
	t_var	*pwd;

	if (!(pwd = var_get(vars, "OLDPWD")))
		return (ft_strdup(""));
	return (ft_strdup(pwd->value));
}

static char	*get_newdir(int argc, char **argv, t_var *vars)
{
	char	*path;
	t_var	*home;

	path = NULL;
	if (argc == 1 && !(home = var_get(vars, "HOME")))
	{
		write(2, "cd: HOME not set\n", 17);
		return (NULL);
	}
	else if (argc == 1 && home)
		path = ft_strdup(home->value);
	else if (argc == 2 && ft_strcmp(argv[1], "-") == 0)
		path = get_oldpwd(vars);
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

	if (!(newdir = get_newdir(cmd->argc, cmd->args, shell->vars)))
		return (1);
	ret = chdir(newdir);
	update_env(&(shell->vars));
	free(newdir);
	return (ret);
}
