/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 13:57:06 by frossiny          #+#    #+#             */
/*   Updated: 2018/11/09 15:06:29 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_strsplit_lst(char const *s, char c)
{
	char	**tab;
	t_list	*lst;
	t_list	*lst_start;
	int		i;

	if (!s)
		return (NULL);
	if (!(tab = ft_strsplit(s, c)))
		return (NULL);
	lst_start = ft_lstnew(*tab, ft_strlen(*tab));
	i = 1;
	lst = lst_start;
	while (tab[i])
	{
		lst->next = ft_lstnew(tab[i], ft_strlen(tab[i]));
		lst = lst->next;
		i++;
	}
	ft_strddel(&tab);
	return (lst_start);
}
