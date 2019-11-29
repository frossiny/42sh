/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:39:39 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/27 15:49:07 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "structs.h"

int		parse(t_token *tokens);
void	par_next(t_parser *parser, int i);

int		par_type_name(t_parser *par);
int		par_type_operator(t_parser *par);
int		par_type_semic(t_parser *par);
int		par_type_redir(t_parser *par);
int		par_type_io_fd(t_parser *par);
int		par_type_jobs(t_parser *par);
int		par_type_conditions(t_parser *par);

#endif
