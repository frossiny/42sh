/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfold.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 14:11:03 by frossiny          #+#    #+#             */
/*   Updated: 2019/02/01 17:12:47 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstfold(t_list **lst, void (*del)(void *, size_t))
{
	t_list	*prev;
	t_list	*current;
	t_list	*next;

	if (!lst || !*lst)
		return ;
	prev = NULL;
	current = *lst;
	while (current)
	{
		next = current->next;
		if (!current->content)
		{
			ft_lstdelone(&current, del);
			if (prev)
				prev->next = next;
			else
				*lst = next;
		}
		prev = current;
		current = next;
	}
}
