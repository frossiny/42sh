/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:29:33 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/14 19:00:41 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

int			b_unsetenv(t_cmd *cmd, t_shell *shell)
{
	int		i;

	if (cmd->argc < 2)
	{
		write(2, "setenv: Too few arguments.\n", 27);
		return (1);
	}
	i = 1;
	while (i < cmd->argc)
	{
		if (!cmd->args[i])
			break ;
		var_delete(&(shell->vars), cmd->args[i++]);
	}
	return (0);
}
