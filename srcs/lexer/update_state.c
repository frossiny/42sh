/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 15:20:20 by frossiny          #+#    #+#             */
/*   Updated: 2019/07/29 15:21:34 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	update_state(t_lexer *lexer, t_state newstate)
{
	lexer->lstate = lexer->state;
	lexer->state = newstate;
}
