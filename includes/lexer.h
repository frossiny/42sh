/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 11:23:56 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/29 15:35:35 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "structs.h"

int			lex_loop(t_shell *shell, char **input, int history);
int			lex_build(t_shell *shell, char **input);
int			lex(char *s, t_lexer *lexer);
t_ex_token	lexer_search(const char *s);
void		lexer_free(t_lexer *lexer);

t_token		*tok_new(t_token_type type, char *content);
t_token		*tok_push(t_token *list, t_token *new);
t_token		*tok_create(t_lexer *lexer, char *content,
							size_t len, t_token_type type);
void		tok_destroy(t_token *token);
int			tok_is_word(t_token *token);
int			tok_is_redirection(t_token *token);
int			tok_is_varexp(t_token *token);
int			tok_is_cmd_comp(t_token *token);
void		tok_replace(t_token *token, char *str);
void		tok_to_input(char **dest, t_token *token);
void		tok_free(t_token *token);
int			lex_is_expansion(t_lexer *lex);
size_t		lex_get_expansion(t_lexer *lex);
t_exp_tok	*lex_new_exp(t_lexer *lexer, const char *op);
void		lex_exp_del(t_lexer *lexer);

void		lex_update_state(t_lexer *lexer, t_state newstate);

int			lex_state_general(t_lexer *lexer);
int			lex_state_quotes(t_lexer *lexer);
int			lex_state_dquotes(t_lexer *lexer);
int			lex_state_comment(t_lexer *lexer);
int			lex_state_escaped(t_lexer *lexer);
int			lex_state_operator(t_lexer *lexer);
int			lex_state_semic(t_lexer *lexer);
int			lex_state_expansions(t_lexer *lexer);

#endif
