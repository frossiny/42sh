/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 14:12:47 by vsaltel           #+#    #+#             */
/*   Updated: 2020/02/18 14:46:06 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alias.h"
#include "libft.h"

t_string	*t_stringdup(t_string *input)
{
	t_string	*new;
	t_string	*deb;

	if (!input)
		return (NULL);
	if (!(new = malloc(sizeof(t_string))))
		return (NULL);
	deb = new;
	while (input)
	{
		new->str = ft_strdup(input->str);
		input = input->next;
		if (!input)
			break ;
		if (!(new->next = malloc(sizeof(t_string))))
			return (NULL);
		new = new->next;
	}
	new->next = NULL;
	return (deb);
}

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

t_string	*add_alias_history(t_string *list, char *str)
{
	t_string	*new;

	if (!str)
		return (NULL);
	if (!(new = (t_string *)malloc(sizeof(t_string))))
		return (NULL);
	new->str = ft_strdup(str);
	new->next = list;
	return (new);
}

int			is_already_solve(t_string *list, char *str)
{
	if (!list)
		return (0);
	while (list && list->str)
	{
		if (!ft_strcmp(list->str, str))
			return (1);
		list = list->next;
	}
	return (0);
}
