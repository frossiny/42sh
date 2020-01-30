/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:29:33 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/30 17:22:26 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "hashtable.h"

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
		if (ft_strequ(cmd->args[i], "PATH"))
			ht_delete();
		var_delete(&(shell->vars), cmd->args[i++]);
	}
	return (0);
}
