/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 19:32:25 by alagroy-          #+#    #+#             */
/*   Updated: 2020/01/21 18:05:57 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"

static char	*g_builtin_tab[] =\
{
	"type",
	"cd",
	"echo",
	"exit",
	"jobs",
	"fg",
	"bg",
	"set",
	"unset",
	"alias",
	"export",
	"unalias",
	"test",
	NULL,
};

t_list		*compl_alias_builtins(t_list *compl_lst, char *compl,
		t_shell *shell)
{
	int		i;
	t_alias	*alias;
	t_list	*new;

	i = -1;
	while (g_builtin_tab[++i])
		if (!ft_strncmp(compl, g_builtin_tab[i], ft_strlen(compl)))
		{
			new = ft_lstnew(g_builtin_tab[i], ft_strlen(g_builtin_tab[i]) + 1);
			ft_lstend(&compl_lst, new);
		}
	alias = shell->alias;
	while (alias)
	{
		if (!ft_strncmp(compl, alias->key, ft_strlen(compl)))
		{
			new = ft_lstnew(alias->key, ft_strlen(alias->key) + 1);
			ft_lstend(&compl_lst, new);
		}
		alias = alias->next;
	}
	return (compl_lst);
}

t_list		*compl_cmd(char *compl, t_shell *shell, int *len)
{
	char	**path;
	t_list	*begin;
	t_list	*new;
	t_var	*var;
	int		i;

	i = -1;
	begin = NULL;
	path = NULL;
	*len = ft_strlen(compl);
	if (ft_strchr(compl, '/'))
		return (compl_file(compl, shell, len));
	if (!(var = var_get(shell->vars, "PATH")))
		return (find_file(".", compl));
	if (!(path = ft_strsplit(var->value, ':')))
		return (NULL);
	while (path && path[++i])
	{
		new = find_file(path[i], compl);
		ft_lstend(&begin, new);
	}
	ft_2dstrdel(&path);
	return (begin);
}
