/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 02:12:48 by pcharrie          #+#    #+#             */
/*   Updated: 2019/11/02 18:19:44 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "utils.h"
#include "shell.h"
#include "libft.h"
#include "variables.h"
#include "builtins.h"
#include "opt.h"

static int	ft_strredupconst(char **s1, char *s2)
{
	char *tmp;

	if (!s1 || !(tmp = ft_strdup(s2)))
		return (0);
	ft_strdel(s1);
	*s1 = tmp;
	return (1);
}

static char	*cd_get_var(char *key)
{
	t_var	*var;
	char	*path;

	if (!(var = var_get(g_shell.vars, key))
		|| !(path = var->value))
	{
		ft_dprintf(2, "42sh: cd: %s not set\n", key);
		return (NULL);
	}
	ft_putendl(path);
	return (ft_strdup(path));
}

int			cd_pathcheck(char *path, char *arg)
{
	struct stat	buf;
	char		buf2[8192];
	char		*error;
	int			c;

	error = NULL;
	if (!path || stat(path, &buf))
		error = "No such file or directory";
	else if (!S_ISDIR(buf.st_mode))
		error = "Not a directory";
	else if (access(path, X_OK) == -1)
		error = "Permission denied";
	if (error)
	{
		ft_dprintf(2, "42sh: cd: %s: %s\n", arg, error);
		ft_strdel(&path);
		return (0);
	}
	return (1);
}

int			cd_chdir(char *path, int follow)
{
	t_var	*pwd;
	char	buff[8192];

	(!follow ? path = cd_buildpath(path) : 0);
	if (!ft_strlen(path))
		ft_strredupconst(&path, "/");
	if (chdir(path))
	{
		ft_strdel(&path);
		return (0);
	}
	if ((pwd = var_get(g_shell.vars, "PWD")))
		var_set(&g_shell.vars, "OLDPWD", pwd->value, 1);
	if (follow)
	{
		getcwd(buff, 8192);
		ft_strredupconst(&g_pwd, buff);
	}
	else
		ft_strredupconst(&g_pwd, path);
	var_set(&g_shell.vars, "PWD", g_pwd, 1);
	ft_strdel(&path);
	return (1);
}

int			cd_getpath(t_cmd *cmd, t_options *opts)
{
	char	*path;
	t_var	*cdp;

	if (!cmd->args[opts->last] || !ft_strcmp(cmd->args[opts->last], "--"))
		path = cd_get_var("HOME");
	else if (!ft_strcmp(cmd->args[opts->last], "-"))
		path = cd_get_var("OLDPWD");
	else if (cmd->args[opts->last][0] != '/'
		&& !ft_strequ(cmd->args[opts->last], ".")
		&& !ft_strequ(cmd->args[opts->last], "..")
		&& (cdp = var_get(g_shell.vars, "CDPATH")) && ft_strlen(cdp->value))
		path = cd_cdpath(cdp, cmd->args[opts->last]);
	else
		path = (cmd->args[opts->last][0] == '/'
			? ft_strdup(cmd->args[opts->last])
			: ft_strjoint(g_pwd, "/", cmd->args[opts->last]));
	if (path && cd_pathcheck(path, cmd->args[opts->last]) &&
		cd_chdir(path, opts->opts && !opts->opts->next
		&& ft_strequ(opts->opts->opt, "P")))
	{
		opt_free(opts);
		return (0);
	}
	opt_free(opts);
	return (1);
}
