/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 13:45:40 by vsaltel           #+#    #+#             */
/*   Updated: 2019/10/29 18:31:49 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "libft.h"

void				free_globing(t_globing_list *list)
{
	t_globing_list	*tmp;

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

t_globing_list		*create_globing(char *str)
{
	char			**tab;
	t_globing_list	*list;
	t_globing_list	*begin;
	int				i;

	if ((tab = ft_strsplit(str, '/')) == NULL)
		return (NULL);
	free(str);
	if (!(list = (t_globing_list *)malloc(sizeof(t_globing_list))))
		return (NULL);
	i = 0;
	list->content = ft_strdup(tab[i]);
	list->next = NULL;
	begin = list;
	while (tab[++i])
	{
		if (!(list->next = (t_globing_list *)malloc(sizeof(t_globing_list))))
			return (NULL);
		list = list->next;
		list->content = ft_strdup(tab[i]);
		list->path = NULL;
		list->next = NULL;
	}
	ft_strddel(&tab);
	return (begin);
}
