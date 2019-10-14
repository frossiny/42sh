/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 20:33:56 by frossiny          #+#    #+#             */
/*   Updated: 2019/07/29 18:51:06 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "shell.h"

typedef struct		s_pipel
{
	t_cmd			*cmd;
	struct s_pipel	*previous;
	struct s_pipel	*next;
}					t_pipel;

typedef struct		s_fd
{
	int				op[2];
	int				np[2];
	int				sfd;
}					t_fd;

typedef struct		s_childs
{
	int				pid;
	struct s_childs	*next;
}					t_childs;

t_anode				*create_node(t_token *ope, t_cmd *cmd);
t_token				*create_ope_node(t_anode **tree, t_token *tokens);
t_token				*create_cmd_node(t_anode **tree, t_token *tokens);
t_cmd				*create_cmd(t_token *exe);

#endif
