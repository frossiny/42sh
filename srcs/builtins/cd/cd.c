/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 16:04:58 by pcharrie          #+#    #+#             */
/*   Updated: 2019/11/02 02:16:17 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "shell.h"
#include "libft.h"
#include "variables.h"
#include "builtins.h"
#include "opt.h"

int			b_cd(t_cmd *cmd, t_shell *shell)
{
	t_options	*opts;

	if (!(opts = opt_parse(cmd, "LP", "cd")))
		return (1);
	while (opts->opts && opts->opts->next)
		opts->opts = opts->opts->next;
	if (opts->ret != 0)
	{
		if (opts->ret == -1)
			ft_putendl_fd("42sh: cd: usage: cd [-L|-P] [dir]", 2);
		return (1);
	}
	if (cmd->argc - opts->last > 1)
	{
		ft_putendl_fd("42sh: cd: too many arguments", 2);
		return (1);
	}
	return (cd_getpath(cmd, opts));
}
