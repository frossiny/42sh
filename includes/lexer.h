/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 11:23:56 by frossiny          #+#    #+#             */
/*   Updated: 2019/07/29 17:32:52 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum	e_state
{
	ST_GENERAL,
	ST_QUOTES,
	ST_DQUOTES,
	ST_ESCAPED,
	ST_COMMENT,
	ST_OPERATOR,
	ST_SEMIC
}				t_state;

typedef struct	s_state_func
{
	t_state		key;
	int			(*lex)();
}				t_state_func;

typedef enum	e_token_type
{
	TOKEN_NULL,
	TOKEN_NAME,
	TOKEN_SEMI,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_REDIRI,
	TOKEN_REDIRO,
	TOKEN_PIPE,
	TOKEN_AGGR,
	TOKEN_IGN
}				t_token_type;

typedef struct	s_ex_token
{
	const char		*op;
	size_t			len;
	t_token_type	type;
	t_state			state;
}				t_ex_token;

typedef struct	s_token
{
	char			*content;
	size_t			len;
	t_token_type	type;
	struct s_token	*next;
}				t_token;

typedef struct	s_lexer
{
	char		*in;
	char		*pin;
	t_token		*tokens;
	t_token		*last_token;
	size_t		size;
	t_state		state;
	t_state		lstate;
}				t_lexer;

void			replace_token(t_token *token, char *str);
void			update_state(t_lexer *lexer, t_state newstate);

int				lex_state_general(t_lexer *lexer);
int				lex_state_quotes(t_lexer *lexer);
int				lex_state_dquotes(t_lexer *lexer);
int				lex_state_comment(t_lexer *lexer);
int				lex_state_escaped(t_lexer *lexer);
int				lex_state_operator(t_lexer *lexer);
int				lex_state_semic(t_lexer *lexer);

#endif
