/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 15:50:15 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/17 15:04:38 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "structs.h"

int		ast_build(t_shell *shell);
int		ast_build_args(t_cmd *cmd, t_var *var);
void	ast_destroy(t_shell *shell);
int		validate_redirection(t_redirect *redir);
void	ast_free_cmd(t_cmd *cmd);

t_anode	*create_node(t_token *ope, t_cmd *cmd);
t_token	*create_ope_node(t_anode **tree, t_token *tokens);
t_token	*create_cmd_node(t_anode **tree, t_token *tokens);
t_cmd	*create_cmd(t_token *exe);

int		ast_is_bg(t_token *tokens);

#endif
