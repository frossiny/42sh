/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 20:33:56 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/26 14:06:38 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READER_H
# define READER_H

# include "structs.h"

int					assign_vars(t_cmd *cmd);

t_anode				*create_node(t_token *ope, t_cmd *cmd);
t_token				*create_ope_node(t_anode **tree, t_token *tokens);
t_token				*create_cmd_node(t_anode **tree, t_token *tokens);
t_cmd				*create_cmd(t_token *exe);

#endif
