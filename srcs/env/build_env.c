/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:50:49 by frossiny          #+#    #+#             */
/*   Updated: 2019/05/15 14:54:48 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

char	**build_env(t_env *env)
{
	char	**envp;
	size_t	i;

	if (!(envp = (char **)malloc(sizeof(char *) * (count_env(env) + 1))))
		exit(1);
	i = 0;
	while (env)
	{
		if (!(envp[i++] = ft_strjoint(env->key, "=", env->value)))
			exit(1);
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}
