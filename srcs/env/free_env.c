/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:52:20 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/11 14:52:36 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	free_env(t_env **env)
{
	t_env	*curr;
	t_env	*next;

	curr = *env;
	while (curr)
	{
		next = curr->next;
		free(curr->key);
		free(curr->value);
		free(curr);
		curr = next;
	}
	*env = NULL;
}
