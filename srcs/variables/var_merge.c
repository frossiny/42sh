/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   va_merge.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 16:16:39 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/08 16:21:25 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "variables.h"

void	var_merge(t_var **dst, t_var *src)
{
	while (src)
	{
		var_set(dst, src->key, src->value, src->export);
		src = src->next;
	}
}
