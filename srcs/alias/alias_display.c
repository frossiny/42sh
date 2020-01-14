/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 17:06:37 by vsaltel           #+#    #+#             */
/*   Updated: 2019/11/06 15:25:36 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "alias.h"

void	alias_display_one(t_alias *alias, char *key)
{
	while (alias)
	{
		if (ft_strcmp(alias->key, key) == 0)
		{
			ft_printf("%s='%s'\n", alias->key, alias->value);
			return ;
		}
		alias = alias->next;
	}
	ft_dprintf(2, "42sh: alias: %s: not found\n", key);
}

void	alias_display_all(t_alias *alias)
{
	while (alias)
	{
		ft_printf("%s='%s'\n", alias->key, alias->value);
		alias = alias->next;
	}
}
