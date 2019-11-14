/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 19:32:25 by alagroy-          #+#    #+#             */
/*   Updated: 2019/11/14 20:40:13 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"

t_list		*compl_cmd(char *compl, t_shell *shell)
{
	char	**path;
	t_list	*begin;
	t_list	*new;
	t_var	*var;
	int		i;

	i = -1;
	begin = NULL;
	path = NULL;
	if (ft_strchr(compl, '/'))
		return (compl_file(compl, shell));
	if (!(var = var_get(shell->vars, "PATH")))
		return (NULL);
	if (!(path = ft_strsplit(var->value, ':')))
		return (NULL);
	while (path && path[++i])
	{
		new = find_file(path[i], compl);
		if (!begin)
			begin = new;
		else
			ft_lstend(&begin, new);
	}
	ft_2dstrdel(path);
	return (begin);
}
