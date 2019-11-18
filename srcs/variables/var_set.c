/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 17:50:15 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/12 16:05:54 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "variables.h"
#include "hashtable.h"

int		var_set(t_var **vars, char *key, char *value, int export)
{
	t_var	*curr;
	t_var	*new;

	if (!key)
		return (0);
	if (ft_strequ(key, "PATH"))
		ht_delete();
	if (!*vars || !(curr = var_get(*vars, key)))
	{
		if (!(new = var_new(key, value, export)))
			return (0);
		if (!*vars)
			*vars = new;
		else
		{
			curr = *vars;
			while (curr && curr->next)
				curr = curr->next;
			curr->next = new;
		}
	}
	else
		return (var_replace(curr, value));
	return (1);
}
