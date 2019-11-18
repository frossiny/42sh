/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 16:59:25 by vsaltel           #+#    #+#             */
/*   Updated: 2019/11/13 14:04:32 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "alias.h"

t_alias		*alias_get(t_alias *alias, char *key)
{
	while (alias)
	{
		if (ft_strcmp(alias->key, key) == 0)
			return (alias);
		alias = alias->next;
	}
	return (NULL);
}
