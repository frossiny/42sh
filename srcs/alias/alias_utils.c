/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 14:12:47 by vsaltel           #+#    #+#             */
/*   Updated: 2019/11/15 17:11:33 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alias.h"
#include "libft.h"

void		free_alias_history(t_string **list)
{
	t_string	*tmp;
	t_string	*lst;

	if (!list || !*list)
		return ;
	lst = *list;
	while (lst)
	{
		free(lst->str);
		tmp = lst->next;
		free(lst);
		lst = tmp;
	}
	*list = NULL;
}

void		add_alias_history(t_string **list, char *str)
{
	t_string	*new;
	char		**tab;
	int			i;

	if (!list || !str)
		return ;
	if (!(tab = ft_strsplit(str, ' ')))
		return ;
	i = -1;
	while (tab[++i])
	{
		if (!(new = (t_string *)malloc(sizeof(t_string))))
			return ;
		new->str = tab[i];
		new->next = *list;
		*list = new;
	}
}

void		maj_alias_history(t_string *list, t_string **hist)
{
	t_string	*tmp;

	if (!list || !hist)
		return ;
	if (!*hist)
	{
		*hist = list;
		return ;
	}
	tmp = *hist;
	if (tmp)
		while (tmp->next)
			tmp = tmp->next;
	while (list)
	{
		tmp->next = list;
		tmp = tmp->next;
		list = list->next;
	}
}

int			is_already_solve(t_string *list, char *str)
{
	if (!list)
		return (0);
	while (list)
	{
		if (!ft_strcmp(list->str, str))
			return (1);
		list = list->next;
	}
	return (0);
}

void		set_loop(t_alias *alias)
{
	if (!alias)
		return ;
	while (alias)
	{
		alias->loop = 0;
		alias = alias->next;
	}
}
