/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unknown.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 16:37:25 by frossiny          #+#    #+#             */
/*   Updated: 2019/01/17 17:51:29 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_unknown(t_arg *arg)
{
	char	*str;
	size_t	len;

	if (arg->type == '\0')
	{
		arg->str = ft_strdup("");
		return ;
	}
	len = arg->width ? arg->width + 1 : 2;
	str = ft_strnew(len);
	if (!str)
		str = ft_strdup("");
	else
	{
		ft_memset(str, arg->zero ? '0' : ' ', len - 1);
		*str = arg->type;
		str[len] = '\0';
		if (!arg->left)
			ft_strrev(str);
	}
	arg->str = str;
}
