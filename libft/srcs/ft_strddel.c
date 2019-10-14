/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strddel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 10:58:06 by frossiny          #+#    #+#             */
/*   Updated: 2019/02/26 15:02:00 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strddel(char ***ap)
{
	int		i;

	if (!ap)
		return ;
	i = 0;
	while ((*ap)[i])
	{
		if ((*ap) + i)
			ft_strdel((*ap) + i);
		i++;
	}
	free(*ap);
	*ap = NULL;
}
