/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2dstrdel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 17:56:02 by pcharrie          #+#    #+#             */
/*   Updated: 2019/11/15 17:39:14 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_2dstrdel(char ***tab)
{
	int i;

	if (!tab
		|| !*tab)
		return ;
	i = 0;
	while ((*tab)[i])
		ft_strdel(&(*tab)[i++]);
	free(*tab);
	*tab = NULL;
}
