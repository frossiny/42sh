/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 16:04:58 by pcharrie          #+#    #+#             */
/*   Updated: 2019/11/01 16:44:07 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/stat.h>
#include "utils.h"
#include "shell.h"
#include "libft.h"
#include "variables.h"
#include "builtins.h"
#include "opt.h"

extern char	*g_pwd;

static int	ft_strredupconst(char **s1, char *s2)
{
	char *tmp;

	if (!s1 || !(tmp = ft_strdup(s2)))
		return (0);
	ft_strdel(s1);
	*s1 = tmp;
	return (1);
}

static char	*cd_get_var(t_shell *shell, char *key)
{
	t_var	*var;
	char	*path;

	if (!(var = var_get(shell->vars, key))
		|| !(path = var->value))
	{
		ft_dprintf(2, "42sh: cd: %s not set\n", key);
		return (NULL);
	}
	ft_putendl(path);
	return (ft_strdup(path));
}

static int	cd_pathcheck(char *path, char *arg)
{
	struct stat	buf;
	char		buf2[8192];
	char		*error;
	int			c;

	error = NULL;
	if (!path)
		return (0);
	if (stat(path, &buf))
		error = "No such file or directory";
	else if (!S_ISDIR(buf.st_mode))
		error = "Not a directory";
	else if (access(path, X_OK) == -1)
		error = "Permission denied";
	if (error)
	{
		ft_dprintf(2, "42sh: cd: %s: %s\n", arg, error);
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

int			b_cd(t_cmd *cmd, t_shell *shell)
{
	t_options	*opts;
	char		*path;
	t_var		*cdpath;

	opts = opt_parse(cmd, "LP", "cd");
	while (opts->opts && opts->opts->next)
		opts->opts = opts->opts->next;
	if (opts->ret != 0)
		(opts->ret == -1 ? ft_putendl_fd("cd: usage: cd [-L|-P] [dir]", 2) : 0);
	else if (cmd->argc - opts->last > 1)
		ft_putendl_fd("42sh: cd: too many arguments", 2);
	else if (!cmd->args[opts->last] || !ft_strcmp(cmd->args[opts->last], "--"))
		path = cd_get_var(shell, "HOME");
	else if (!ft_strcmp(cmd->args[opts->last], "-"))
		path = cd_get_var(shell, "OLDPWD");
	else if (cmd->args[opts->last][0] != '/' &&
		(cdpath = var_get(g_shell.vars, "CDPATH")))
		path = ft_strjoint(cdpath->value, "/", cmd->args[opts->last]);
	else
		path = (cmd->args[opts->last][0] == '/'
			? ft_strdup(cmd->args[opts->last])
			: ft_strjoint(g_pwd, "/", cmd->args[opts->last]));
	return (!(path && cd_pathcheck(path, cmd->args[opts->last])
		&& cd_chdir(path, opts->opts && !opts->opts->next
		&& ft_strequ(opts->opts->opt, "P"))));
}
