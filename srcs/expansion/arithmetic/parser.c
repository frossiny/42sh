/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 18:45:57 by alagroy-          #+#    #+#             */
/*   Updated: 2019/11/14 10:33:47 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arithmetic.h"

int		g_ae_parse_tab[5][NBR_TYPE] =\
{
	{-1, 1, 2, -1, -1, -1, -1, -1, -2},
	{-1, -1, -1, 3, 4, 4, 3, 3, -2},
	{-1, -1, -1, 3, -1, -1, 3, 3, -2},
	{-1, 1, 2, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, 3, -1, -1, 3, 3, -2},
};

int		parse_aetoken(t_list *token_list)
{
	t_list	*tmp;
	int		state;
	int		j;

	state = 0;
	tmp = token_list;
	while (state >= 0)
	{
		j = -1;
		while (++j < NBR_TYPE)
			if ((int)((t_ae_token *)tmp->content)->type == j)
				break ;
		if (j < NBR_TYPE)
			state = g_ae_parse_tab[state][j];
		else
			return (AEPFAILURE);
		tmp = tmp->next;
		if (!tmp)
			break ;
	}
	return (state);
}
