/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 18:49:27 by vsaltel           #+#    #+#             */
/*   Updated: 2019/10/18 18:49:28 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "expansion.h"
#include "lexer.h"
#include "utils.h"

#include <dirent.h>

void			strswitch(char **dest, char *new)
{
	char *tmp;

	if (!dest || !*dest || !new || *dest == new)
		return ;
	tmp = *dest;
	*dest = new;
	free(tmp);
}

void			display_list(t_globing_list *list)
{
	while (list)
	{
		ft_printf("list -> %s\n", list->content);
		list = list->next;
	}
}

char			*pull_multi_occ(char *str, char occ)
{
	int	i;
	int	j;
	char	*tmp;
	char	*curr;

	curr = ft_strdup(str);
	i = -1;
	while (curr[++i])
	{
		j = i;
		while (curr[j] == occ)
			j++;	
		if (j > i + 1)
		{
			tmp = ft_strndup(curr, i + 1);
			curr = ft_strfjoin(tmp, curr + j, curr);
			free(tmp);
		}
	}
	return (curr);
}

void			free_globing(t_globing_list *list)
{
	t_globing_list	*tmp;

	if (!list)
		return ;
	while (list)
	{
		free(list->content);
		tmp = list;
		list = list->next;
		free(tmp);
	}
}

t_globing_list		*create_globing(char *str)
{
	char		**tab;
	t_globing_list	*list;
	t_globing_list	*begin;
	int		i;

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
		list->next = NULL;
	}
	ft_strddel(&tab);
	return (begin);
}

int			replace_globing(t_token *token, t_var *vars)
{
	char		*tmp;
	t_globing	glob;

	while (token && is_word_token(token))
	{
		glob.root = (token->content[0] == '/');
		glob.list = create_globing(pull_multi_occ(token->content, '*'));	
		display_list(glob.list);
		token = token->next;
		free_globing(glob.list);
	}
	return (1);
}
