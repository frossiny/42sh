/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_delete.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 18:49:07 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/14 19:06:20 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "variables.h"

int		var_delete(t_var **vars, char *key)
{
	t_var	*curr;
	t_var	*last;

	if (!vars)
		return (0);
	last = NULL;
	curr = *vars;
	while (curr)
	{
		if (ft_strequ(curr->key, key))
		{
			if (last)
				last->next = curr->next;
			else
				*vars = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			return (1);
		}
		last = curr;
		curr = curr->next;
	}
	return (0);
}
