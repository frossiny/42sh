/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 11:23:56 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/14 14:28:34 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "structs.h"

int			lex(char *s, t_lexer *lexer);
int			is_escaped(char *s, size_t index, int endquote);
t_ex_token	lexer_search(const char *s);
void		destroy_lexer(t_lexer *lexer);
t_token		*push_token(t_token *list, t_token *new);
t_token		*create_token(t_lexer *lexer, char *content,
							size_t len, t_token_type type);
void		destroy_tokens(t_token *token);
int			is_word_token(t_token *token);

void		replace_token(t_token *token, char *str);
void		update_state(t_lexer *lexer, t_state newstate);

int			lex_state_general(t_lexer *lexer);
int			lex_state_quotes(t_lexer *lexer);
int			lex_state_dquotes(t_lexer *lexer);
int			lex_state_comment(t_lexer *lexer);
int			lex_state_escaped(t_lexer *lexer);
int			lex_state_operator(t_lexer *lexer);
int			lex_state_semic(t_lexer *lexer);

#endif
