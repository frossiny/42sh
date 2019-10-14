/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 14:33:18 by frossiny          #+#    #+#             */
/*   Updated: 2019/02/01 17:18:26 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "converter.h"

void	convert(t_arg *arg)
{
	int		i;

	i = 0;
	if (!is_type(arg->type))
		return (handle_unknown(arg));
	while (g_convlst[i].dtype)
	{
		if (ft_strchr(g_convlst[i].dtype, arg->type))
		{
			g_convlst[i].func(arg);
			return ;
		}
		i++;
	}
}
