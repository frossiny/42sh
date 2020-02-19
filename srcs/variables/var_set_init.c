/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_set_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 18:19:02 by vsaltel           #+#    #+#             */
/*   Updated: 2020/02/19 18:24:27 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "libft.h"
#include "shell.h"

static void	check_shlvl(void)
{
	t_var	*shlvl;
	int		int_shlvl;
	char	*tmp;

	int_shlvl = 1;
	shlvl = var_get(g_shell.vars, "SHLVL");
	if (shlvl && (int_shlvl = ft_atoi(shlvl->value) + 1) && int_shlvl >= 1002)
	{
		ft_dprintf(2,
			"42sh: warning: shell level (%d) too high, resetting to 1\n",
			int_shlvl);
		int_shlvl = 1;
	}
	if (int_shlvl < 0)
		int_shlvl = 0;
	if ((tmp = ft_itoa(int_shlvl)))
	{
		var_set(&g_shell.vars, "SHLVL", tmp, 1);
		ft_strdel(&tmp);
	}
	else
		var_set(&g_shell.vars, "SHLVL", "1", 1);
}

void		var_set_init(void)
{
	char	buff[MAX_PWD_LEN];
	t_var	*pwd;
	DIR		*dir;

	if ((pwd = var_get(g_shell.vars, "PWD"))
		&& (dir = opendir(pwd->value)))
	{
		closedir(dir);
		g_pwd = ft_strdup(pwd->value);
	}
	else
	{
		getcwd(buff, MAX_PWD_LEN);
		g_pwd = ft_strdup(buff);
	}
	var_set(&g_shell.vars, "PWD", g_pwd, 1);
	check_shlvl();
}
