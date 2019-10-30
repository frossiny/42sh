/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 13:45:40 by vsaltel           #+#    #+#             */
/*   Updated: 2019/10/30 13:23:08 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "libft.h"

void				free_globbing(t_globbing_list *list)
{
	t_globbing_list	*tmp;

	if (!list)
		return ;
	while (list)
	{
		free(list->path);
		free(list->content);
		tmp = list;
		list = list->next;
		free(tmp);
	}
}

t_globbing_list		*create_globbing(char *str)
{
	char			**tab;
	t_globbing_list	*list;
	t_globbing_list	*begin;
	int				i;

	if ((tab = ft_strsplit(str, '/')) == NULL)
		return (NULL);
	free(str);
	if (!(list = (t_globbing_list *)malloc(sizeof(t_globbing_list))))
		return (NULL);
	i = 0;
	list->content = ft_strdup(tab[i]);
	list->next = NULL;
	begin = list;
	while (tab[++i])
	{
		if (!(list->next = (t_globbing_list *)malloc(sizeof(t_globbing_list))))
			return (NULL);
		list = list->next;
		list->content = ft_strdup(tab[i]);
		list->path = NULL;
		list->next = NULL;
	}
	ft_strddel(&tab);
	return (begin);
}
