/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:29:33 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/17 15:20:32 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

int			b_unset(t_cmd *cmd, t_shell *shell)
{
	int		i;

	if (cmd->argc < 2)
	{
		write(2, "unset: Too few arguments.\n", 26);
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
