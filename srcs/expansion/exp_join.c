/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_join.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 12:52:11 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/13 14:46:51 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion.h"

void	exp_join(t_expansion *e, char *tmp, int noescape)
{
	if (!tmp)
		return ;
	if (e->new)
	{
		if (e->isquote == 1 || noescape)
			e->new = ft_strfjoin(e->new, tmp, e->new);
		else if (e->isquote == 2 || noescape)
			e->new = dquotes_join_escape(e->new, tmp);
		else
			e->new = strjoin_escape(e->new, tmp);
	}
	else
	{
		if (e->isquote == 1 || noescape)
			e->new = ft_strdup(tmp);
		else if (e->isquote == 2 || noescape)
			e->new = dquotes_dup_escape(tmp);
		else
			e->new = strdup_escape(tmp);
	}
	free(tmp);
}
