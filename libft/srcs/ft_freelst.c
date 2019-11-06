/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freelst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:22:20 by vsaltel           #+#    #+#             */
/*   Updated: 2019/10/23 15:25:13 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_freelst(t_list **alst)
{
	t_list	*cl;
	t_list	*next;

	cl = *alst;
	while (cl)
	{
		next = cl->next;
		free(cl->content);
		free(cl);
		cl = NULL;
		cl = next;
	}
	*alst = NULL;
}
