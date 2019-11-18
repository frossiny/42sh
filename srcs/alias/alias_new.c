/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 15:51:03 by vsaltel           #+#    #+#             */
/*   Updated: 2019/11/18 15:13:38 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "alias.h"

int			alias_maj(t_alias *alias, char *key, char *value)
{
	while (alias)
	{
		if (ft_strcmp(key, alias->key) == 0)
		{
			free(alias->value);
			alias->value = value;
			return (1);
		}
		alias = alias->next;
	}
	return (0);
}

t_alias		*alias_malloc(char *key, char *value)
{
	t_alias *new;

	if (!(new = malloc(sizeof(t_alias))))
		return (NULL);
	new->next = NULL;
	new->key = key;
	new->value = value;
	return (new);
}

int			add_alias_aft(t_alias *alias, char *key, char *value)
{
	t_alias *tmp;
	t_alias *bef;

	bef = NULL;
	while (alias)
	{
		if (bef && ft_strcmp(key, alias->key) < 0)
		{
			bef->next = alias_malloc(key, value);
			bef->next->next = alias;
			return (1);
		}
		if (!alias->next)
		{
			alias->next = alias_malloc(key, value);
			return (1);
		}
		bef = alias;
		alias = alias->next;
	}
	return (0);
}

int			alias_new(t_alias **list, char *key, char *value)
{
	t_alias *alias;

	if (!list || !key || !value)
		return (0);
	if (!(*list))
	{
		*list = alias_malloc(key, value);
		return (1);
	}
	alias = *list;
	if (alias_maj(alias, key, value))
		return (1);
	if (ft_strcmp(key, alias->key) < 0)
	{
		*list = alias_malloc(key, value);
		(*list)->next = alias;
		return (1);
	}
	return (add_alias_aft(alias, key, value));
}
