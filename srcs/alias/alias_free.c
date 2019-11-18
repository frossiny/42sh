/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 16:24:05 by vsaltel           #+#    #+#             */
/*   Updated: 2019/11/18 15:13:48 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alias.h"

void	alias_free_one(t_alias *alias)
{
	if (!alias)
		return ;
	free(alias->key);
	free(alias->value);
	free(alias);
}

void	alias_free_all(t_alias **list)
{
	t_alias *alias;
	t_alias *tmp;

	if (!list || !*list)
		return ;
	alias = *list;
	while (alias)
	{
		tmp = alias->next;
		alias_free_one(alias);
		alias = tmp;
	}
	*list = NULL;
}
