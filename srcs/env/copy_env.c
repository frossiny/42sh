/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:51:11 by frossiny          #+#    #+#             */
/*   Updated: 2019/05/15 14:54:54 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

t_env	*copy_env(char **envp, int inc)
{
	t_env	*env;
	char	**tmp;

	env = NULL;
	tmp = NULL;
	while (envp && *envp)
	{
		tmp = ft_strsplit(*envp, '=');
		new_envl(&env, tmp[0], tmp[1], inc);
		ft_strddel(&tmp);
		envp++;
	}
	return (env);
}
