/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 18:45:57 by alagroy-          #+#    #+#             */
/*   Updated: 2020/01/07 16:16:51 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arithmetic.h"

int		g_ae_parse_tab[5][NBR_TYPE] =\
{
	{-1, 1, 2, -1, -1, -1, -1, -1, -2},
	{-1, -1, -1, 3, 4, 4, 3, 3, -2},
	{-1, -1, -1, 3, 2, 2, 3, 3, -2},
	{-1, 1, 2, -1, 3, 3, -1, -1, -1},
	{-1, -1, -1, 3, 4, 4, 3, 3, -2},
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
		j = (int)((t_ae_token *)tmp->content)->type;
		if (j < NBR_TYPE)
			state = g_ae_parse_tab[state][j];
		else
		{
			ft_dprintf(2, "42sh: syntax error in expression\n");
			return (AEPFAILURE);
		}
		tmp = tmp->next;
		if (!tmp)
			break ;
	}
	if (state == AEPFAILURE)
		ft_dprintf(2, "42sh: syntax error in expression\n");
	return (state);
}
