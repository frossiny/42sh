/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 06:37:24 by pcharrie          #+#    #+#             */
/*   Updated: 2019/11/13 17:25:19 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include "utils.h"
#include "shell.h"
#include "libft.h"
#include "variables.h"
#include "builtins.h"
#include "opt.h"

void	shell_exec_cmd(char *cmd)
{
	char *tmp;

	if ((tmp = ft_strdup(cmd)))
		g_return = eval_exec(&tmp);
}

int		fc_get_mode(t_fc_vars *fc)
{
	if (fc->exec)
		return (1);
	if (fc->list)
		return (2);
	return (3);
}

void	fc_exec_tab(t_fc_vars *fc)
{
	int i;

	i = 0;
	while (fc->tab[i])
	{
		ft_putendl(fc->tab[i++]);
		//shell_exec_cmd(fc->tab[i++]);
	}
}

void	fc_exec_file(void)
{
	
}
