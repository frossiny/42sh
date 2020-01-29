/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_create_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 13:05:37 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/28 13:07:25 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_anode			*ast_create_node(t_token *ope, t_cmd *cmd)
{
	t_anode	*node;

	if (!(node = (t_anode *)malloc(sizeof(t_anode))))
		exit(-1);
	node->ope = ope;
	node->cmd = cmd;
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;
	return (node);
}
