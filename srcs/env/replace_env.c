/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 16:47:41 by frossiny          #+#    #+#             */
/*   Updated: 2019/05/22 16:58:46 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

t_env	*replace_env(t_env *env, char *key, char *new)
{
	while (env)
	{
		if (ft_strequ(env->key, key))
		{
			if (env->value)
				free(env->value);
			env->value = ft_strdup(new);
			return (env);
		}
		env = env->next;
	}
	return (NULL);
}
