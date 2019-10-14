/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 14:05:14 by frossiny          #+#    #+#             */
/*   Updated: 2019/05/02 14:06:50 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_env	*dup_env(t_env *env, int option)
{
	t_env	*nenv;

	if (option)
		return (NULL);
	nenv = NULL;
	while (env)
	{
		new_envl(&nenv, env->key, env->value, 0);
		env = env->next;
	}
	return (nenv);
}
