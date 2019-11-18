/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 19:58:51 by alagroy-          #+#    #+#             */
/*   Updated: 2019/11/18 17:37:10 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"

t_list		*compl_var(char *compl, t_shell *shell, int *len)
{
	t_list	*begin;
	t_list	*new;
	t_var	*tmp;
	char	*var;
	int		i;

	i = 0;
	while (compl[i] && (compl[i] == '$' || compl[i] == '{'))
		i++;
	if (!(var = ft_strsub(compl, i, ft_strlen(compl) - i)))
		return (NULL);
	*len = ft_strlen(var);
	begin = NULL;
	tmp = shell->vars;
	while (tmp)
	{
		if (!ft_strncmp(var, tmp->key, ft_strlen(var)))
		{
			new = ft_lstnew(tmp->key, ft_strlen(tmp->key) + 1);
			ft_lstend(&begin, new);
		}
		tmp = tmp->next;
	}
	ft_strdel(&var);
	return (begin);
}
