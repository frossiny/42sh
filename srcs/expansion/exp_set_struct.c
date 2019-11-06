/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_set_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 12:48:47 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/04 12:49:22 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

void		exp_set_struct(t_expansion *exp, char *content)
{
	exp->i = -1;
	exp->li = 0;
	exp->isquote = 0;
	exp->str = content;
	exp->new = NULL;
}
