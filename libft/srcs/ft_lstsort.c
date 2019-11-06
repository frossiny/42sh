/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:32:25 by vsaltel           #+#    #+#             */
/*   Updated: 2019/10/23 17:07:57 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	lst_len(t_list *lst)
{
	size_t	len;

	if (!lst)
		return (0);
	len = 0;
	while (lst)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}

static void		split_list(t_list **left, t_list **right, size_t lstlen)
{
	t_list	*nlst;
	size_t	mid;

	if (!left)
		return ;
	mid = lstlen / 2;
	*right = *left;
	while (mid-- > 1)
		*right = (*right)->next;
	nlst = (*right)->next;
	(*right)->next = NULL;
	(*right) = nlst;
}

static t_list	*sort_merge(t_list *left, t_list *right)
{
	t_list	*lst;
	long	cmp;

	if (!left)
		return (right);
	else if (!right)
		return (left);
	cmp = ft_strcmp(left->content, right->content);
	if (cmp < 0)
	{
		lst = left;
		lst->next = sort_merge(left->next, right);
	}
	else
	{
		lst = right;
		lst->next = sort_merge(left, right->next);
	}
	return (lst);
}

void			ft_lstsort(t_list **list)
{
	size_t	lstlen;
	t_list	*left;
	t_list	*right;

	if (!*list || !(*list)->next)
		return ;
	lstlen = lst_len(*list);
	left = *list;
	split_list(&left, &right, lstlen);
	ft_lstsort(&left);
	ft_lstsort(&right);
	*list = sort_merge(left, right);
}
