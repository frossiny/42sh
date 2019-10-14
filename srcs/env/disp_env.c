/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disp_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:49:51 by frossiny          #+#    #+#             */
/*   Updated: 2019/05/15 14:55:09 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "shell.h"

int		disp_env(t_env *env)
{
	if (!env)
		return (0);
	while (env)
	{
		ft_printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}
