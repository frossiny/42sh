/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 18:10:31 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/14 18:11:08 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "variables.h"

void	var_destroy(t_var **vars)
{
	t_var	*curr;
	t_var	*next;

	curr = *vars;
	while (curr)
	{
		next = curr->next;
		free(curr->key);
		free(curr->value);
		free(curr);
		curr = next;
	}
	*vars = NULL;
}
