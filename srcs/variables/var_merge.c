/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_merge.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 16:16:39 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/18 16:10:20 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "variables.h"

void	var_merge(t_var **dst, t_var *src)
{
	t_var	*env;
	t_var	*cur;

	env = NULL;
	while (src)
	{
		var_set(&env, src->key, src->value, src->export);
		src = src->next;
	}
	cur = *dst;
	while (cur)
	{
		var_set(&env, cur->key, cur->value, cur->export);
		cur = cur->next;
	}
	var_destroy(dst);
	*dst = env;
}
