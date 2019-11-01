/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_push.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 12:27:16 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/17 16:34:40 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_token		*tok_push(t_token *list, t_token *new)
{
	while (list->next)
		list = list->next;
	if (!list)
		return (NULL);
	list->next = new;
	return (new);
}
