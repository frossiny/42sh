/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 18:21:00 by frossiny          #+#    #+#             */
/*   Updated: 2018/11/09 15:04:06 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*cl;
	t_list	*next;

	cl = *alst;
	while (cl)
	{
		next = cl->next;
		ft_lstdelone(&cl, del);
		cl = next;
	}
	*alst = NULL;
}
