/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_envl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:51:48 by frossiny          #+#    #+#             */
/*   Updated: 2019/05/22 16:57:54 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

t_env	*new_envl(t_env **env, char *key, char *value, int inc)
{
	t_env	*new;
	t_env	*tmp;

	if (exists_env(*env, key))
		return (replace_env(*env, key, value));
	if (!(new = (t_env *)malloc(sizeof(t_env))))
		return (NULL);
	new->key = ft_strdup(key);
	if (inc && ft_strcmp("SHLVL", key) == 0)
		new->value = ft_itoa(ft_atoi(value ? value : "") + 1);
	else if (!(new->value = ft_strdup(value ? value : "")))
		exit(1);
	new->next = NULL;
	if (*env)
	{
		tmp = *env;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*env = new;
	return (new);
}
