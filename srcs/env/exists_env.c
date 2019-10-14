/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exists_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 16:51:23 by frossiny          #+#    #+#             */
/*   Updated: 2019/05/22 16:58:34 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

int		exists_env(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strequ(env->key, key))
			return (1);
		env = env->next;
	}
	return (0);
}
