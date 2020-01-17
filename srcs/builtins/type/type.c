/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 17:40:24 by vsaltel           #+#    #+#             */
/*   Updated: 2020/01/17 16:57:40 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "structs.h"
#include "libft.h"

int			b_type(t_cmd *cmd, t_shell *shell)
{
	int		i;
	size_t	find;

	find = 0;
	i = 1;
	while (i < cmd->argc)
	{
		if (!type_alias(cmd->args[i], &find, shell->alias))
			if (!type_builtin(cmd->args[i], &find))
				if (!type_hashtable(cmd->args[i], &find))
					if (!type_env_path(cmd->args[i], &find, shell->vars))
						if (!type_path(cmd->args[i], &find))
							ft_dprintf(2, "42sh: type: %s: not found\n",
															cmd->args[i]);
		i++;
	}
	if (find)
		return (0);
	return (1);
}
