/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 14:33:57 by frossiny          #+#    #+#             */
/*   Updated: 2018/11/09 15:08:41 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelstr(void *s, size_t len)
{
	char	*str;

	str = (char *)s;
	if (!str || len <= 0)
		return ;
	ft_strdel(&str);
}
