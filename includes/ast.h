/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 15:50:15 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/14 18:22:11 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "structs.h"

int		build_ast(t_shell *shell);
int		build_args(t_cmd *cmd, t_var *var);
void	destroy_ast(t_shell *shell);
int		validate_redirection(t_redirect *redir);

#endif
