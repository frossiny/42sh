/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   histo_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 12:18:13 by vsaltel           #+#    #+#             */
/*   Updated: 2019/12/04 15:17:47 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"
#include "expansion.h"
#include "utils.h"

static int		histo_previous(t_expansion *e, t_history history, char **needle)
{
	*needle = ft_strdup("!");
	if (history.size == 0)
		return (1);
	e->new = ft_strfjoin(e->new, history.lst->str, e->new);
	return (0);
}

static int		histo_strstr(t_expansion *e, t_history history, char **needle)
{
	t_histo_lst	*lst;

	*needle = exp_sub_pattern(e->str, e->i, 0);
	if (history.size == 0)
		return (1);
	lst = history.lst;
	while (lst)
	{
		if (histo_cmp(*needle, lst->str))
		{
			e->new = ft_strfjoin(e->new, lst->str, e->new);
			break;
		}
		lst = lst->next;
	}
	return (lst ? 0 : 1);
}

static int		histo_index_exp(t_expansion *e, t_history history, char **needle, int rev)
{
	size_t		index;
	t_histo_lst	*lst;

	*needle = exp_sub_pattern(e->str, e->i, 1);
	index = ft_atoi(e->str + e->i);
	if (history.size == 0 || index < 1 || index > history.size)
		return (1);
	lst = history.lst;
	if (rev)
		while (--index && lst)	
			lst = lst->next;
	else
	{
		while (lst->next)
			lst = lst->next;
		while (--index && lst)	
			lst = lst->prev;
	}
	e->new = ft_strfjoin(e->new, lst->str, e->new);
	return (0);
}

static int		histo_complete(t_expansion *e, t_history history, int *find)
{
	int		res;
	int		rev;
	char	*tmp;

	(*find)++;
	tmp = NULL;
	rev = 0;
	res = 0;
	if (e->i > 0)	
		e->new = ft_strjoinf(e->new, ft_strsub(e->str, e->li, e->i - e->li));
	if (e->str[++(e->i)] && e->str[e->i] == '-' && !is_escaped(e->str, e->i, 0) && e->i++)
		rev = 1;
	if (e->str[e->i] && e->str[e->i] == '!')
		res = histo_previous(e, history, &tmp);
	else if (e->str[e->i] && ft_isdigit(e->str[e->i]))
		res = histo_index_exp(e, history, &tmp, rev);
	else
		res = histo_strstr(e, history, &tmp);
	if (res)
		ft_dprintf(2, "42sh: !%s%s: event not found\n", rev ? "-" : "", tmp);
	maj_last_index(e, tmp);
	return (res);
}

int				histo_expansion(t_shell *shell, char **input)
{
	t_expansion	e;
	int			find;

	find = 0;
	exp_set_struct(&e, *input);
	e.new = ft_strdup("");
	while (e.str[++(e.i)])
	{
		if (e.str[e.i] == '\'' && !is_escaped(e.str, e.i, 0))
			e.isquote = (e.isquote ? 0 : 1);
		if (e.str[e.i] == '!' && !is_escaped(e.str, e.i, 0) && e.str[e.i + 1] && e.str[e.i + 1] != ' ' && !e.isquote)
			if (histo_complete(&e, shell->history, &find))
			{
				free(e.new);
				return (1);
			}
	}
	e.new = ft_strjoinf(e.new, ft_strsub(e.str, e.li, e.i - e.li));
	free(*input);
	*input = e.new;
	if (find)
		ft_printf("%s\n", *input);
	return (0);
}
