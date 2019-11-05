/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 17:06:37 by vsaltel           #+#    #+#             */
/*   Updated: 2019/11/05 17:52:20 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "alias.h"

void	alias_display_one(t_alias *alias, char *key)
{
	while (alias)
	{
		if (ft_strcmp(alias->key, key) == 0)
			ft_printf("alias %s='%s'\n", alias->key, alias->value);
		alias = alias->next;
	}
}

void	alias_display_all(t_alias *alias)
{
	while (alias)
	{
		ft_printf("alias %s='%s'\n", alias->key, alias->value);
		alias = alias->next;
	}
}
