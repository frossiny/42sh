/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 15:50:15 by frossiny          #+#    #+#             */
/*   Updated: 2019/08/12 15:05:44 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "shell.h"

typedef struct		s_redirect
{
	int					done : 1;
	int					append : 1;
	int					filedes;
	int					p[2];
	t_token_type		type;
	t_token				*value;
	struct s_redirect	*next;
}					t_redirect;

typedef struct		s_cmd
{
	t_token			*exe;
	char			**args;
	int				argc;
	t_redirect		*redir;
	int				allow_builtins : 1;
}					t_cmd;

typedef struct		s_anode
{
	t_token			*ope;
	t_cmd			*cmd;
	struct s_anode	*parent;
	struct s_anode	*left;
	struct s_anode	*right;
}					t_anode;

int					validate_redirection(t_redirect *redir);

#endif
