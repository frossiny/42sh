/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 18:50:21 by frossiny          #+#    #+#             */
/*   Updated: 2018/11/08 18:58:10 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*fl;
	t_list	*nc;

	if (!lst)
		return (NULL);
	fl = f(lst);
	nc = fl;
	while (lst->next)
	{
		nc->next = f(lst->next);
		lst = lst->next;
		nc = nc->next;
	}
	return (fl);
}
