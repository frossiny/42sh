/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_dup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 13:25:22 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/17 13:26:26 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "variables.h"

t_var	*var_dup(t_var *src)
{
	t_var	*new;

	if (!src || !(new = var_new(src->key, src->value, 0)))
		return (NULL);
	return (new);
}
