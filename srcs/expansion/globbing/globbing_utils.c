/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 13:45:40 by vsaltel           #+#    #+#             */
/*   Updated: 2019/10/31 16:52:55 by vsaltel          ###   ########.fr       */
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

void				set_globbing(t_globbing_list *list, char *str)
{
	list->content = str;
	list->next = NULL;
	list->path = NULL;
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
	i = 0;
	if (!(list = (t_globbing_list *)malloc(sizeof(t_globbing_list))))
		return (NULL);
	set_globbing(list, ft_strdup(tab[i]));
	begin = list;
	while (tab[++i])
	{
		if (!(list->next = (t_globbing_list *)malloc(sizeof(t_globbing_list))))
			return (NULL);
		list = list->next;
		set_globbing(list, ft_strdup(tab[i]));
	}
	ft_strddel(&tab);
	return (begin);
}
