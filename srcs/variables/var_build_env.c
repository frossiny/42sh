/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_build_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 18:31:50 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/24 12:53:48 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "variables.h"

static int	count_env(t_var *vars)
{
	int		c;

	c = 0;
	while (vars)
	{
		c += (vars->export);
		vars = vars->next;
	}
	return (c);
}

char		**var_build_env(t_var *vars)
{
	char	**envp;
	size_t	i;

	if (!(envp = (char **)malloc(sizeof(char *) * (count_env(vars) + 1))))
		exit(1);
	i = 0;
	while (vars)
	{
		if (vars->export)
			if (!(envp[i++] = ft_strjoint(vars->key, "=", vars->value)))
				exit(1);
		vars = vars->next;
	}
	envp[i] = NULL;
	return (envp);
}
