/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 18:05:24 by frossiny          #+#    #+#             */
/*   Updated: 2018/11/14 12:37:31 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*l;

	if (!(l = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	l->content = (void *)content;
	if (!content)
	{
		l->content = NULL;
		l->content_size = 0;
		l->next = NULL;
		return (l);
	}
	if (!(l->content = ft_memalloc(content_size)))
		return (NULL);
	ft_memcpy(l->content, content, content_size);
	l->content_size = content_size;
	l->next = NULL;
	return (l);
}
