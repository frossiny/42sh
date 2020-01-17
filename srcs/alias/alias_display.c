/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 17:06:37 by vsaltel           #+#    #+#             */
/*   Updated: 2020/01/17 16:59:03 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "alias.h"

int		alias_display_one(t_alias *alias, char *key)
{
	while (alias)
	{
		if (ft_strcmp(alias->key, key) == 0)
		{
			ft_printf("%s='%s'\n", alias->key, alias->value);
			return (1);
		}
		alias = alias->next;
	}
	ft_dprintf(2, "42sh: alias: %s: not found\n", key);
	return (0);
}

void	alias_display_all(t_alias *alias)
{
	while (alias)
	{
		ft_printf("%s='%s'\n", alias->key, alias->value);
		alias = alias->next;
	}
}
