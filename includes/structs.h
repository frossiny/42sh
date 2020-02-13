/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:23:53 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/31 17:23:57 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdlib.h>
# include <termios.h>
# include "libft.h"

/*
** Arithmetic Expansions structs
*/
typedef enum		e_ae_type
{
	ERROR,
	WORD,
	NUM,
	OPERATOR,
	INCR,
	DECR,
	COMP,
	SEP,
	EOI,
}					t_ae_type;

typedef enum		e_ae_value
{
	PLUS,
	PPLUS,
	MINUS,
	MMINUS,
	MULT,
	DIV,
	MOD,
	EQU,
	NEQU,
	GREAT,
	GREATEQ,
	LESS,
	LESSEQ,
	AND,
	OR,
}					t_ae_value;

typedef struct		s_ae_token
{
	t_ae_type		type;
	long			num_value;
	char			*word;
	t_ae_value		value;
}					t_ae_token;

typedef struct		s_fill_aevalue
{
	char			*str;
	t_ae_value		value;
}					t_fill_aevalue;

/*
** Alias structure
*/
typedef struct		s_alias
{
	char			*key;
	char			*value;
	int				loop;
	struct s_alias	*next;
}					t_alias;

/*
** Variables structure
*/
typedef struct		s_var
{
	char			*key;
	char			*value;
	int				export;
	struct s_var	*next;
}					t_var;

/*
** Lexer structs
*/
typedef enum		e_state
{
	ST_GENERAL,
	ST_QUOTES,
	ST_DQUOTES,
	ST_ESCAPED,
	ST_COMMENT,
	ST_OPERATOR,
	ST_EXPANSIONS
}					t_state;

typedef struct		s_state_func
{
	t_state		key;
	int			(*lex)();
}					t_state_func;

typedef enum		e_token_type
{
	TOKEN_NULL,
	TOKEN_NAME,
	TOKEN_ASSIGNMENT,
	TOKEN_VAR,
	TOKEN_ARITHMETIC,
	TOKEN_SEMI,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_IO_FD,
	TOKEN_REDIRI,
	TOKEN_REDIRO,
	TOKEN_PIPE,
	TOKEN_AGGR,
	TOKEN_IGN,
	TOKEN_JOBS
}					t_token_type;

typedef struct		s_ex_token
{
	const char		*op;
	size_t			len;
	t_token_type	type;
	t_state			state;
}					t_ex_token;

typedef struct		s_token
{
	char			*content;
	size_t			len;
	t_token_type	type;
	struct s_token	*next;
}					t_token;

/*
**	Used in expansions lexing
*/
typedef struct		s_exp_tok
{
	char				*op;
	struct s_exp_tok	*next;
}					t_exp_tok;

typedef struct		s_lexer
{
	char		*in;
	char		*pin;
	t_token		*tokens;
	t_token		*last_token;
	size_t		size;
	t_state		state;
	t_state		lstate;
	t_exp_tok	*exps;
}					t_lexer;

/*
** Parser structures
*/
typedef struct		s_type_func
{
	t_token_type	key;
	int				(*fnc)();
}					t_type_func;

typedef struct		s_parser
{
	t_token		*tokens;
	int			i;
	char		can_var;
}					t_parser;

/*
** AST structures
*/
typedef struct		s_redirect
{
	int					done : 1;
	int					append : 1;
	int					filedes;
	t_token_type		type;
	t_token				*value;
	char				**heredoc;
	struct s_redirect	*next;
}					t_redirect;

typedef struct		s_cmd
{
	t_token			*tokens;
	t_token			*exe;
	char			**args;
	int				argc;
	t_redirect		*redir;
	int				allow_builtins : 1;
	t_var			*tenv;
	int				is_bg;
	int				exe_found;
}					t_cmd;

typedef struct		s_anode
{
	t_token			*ope;
	t_cmd			*cmd;
	struct s_anode	*parent;
	struct s_anode	*left;
	struct s_anode	*right;
}					t_anode;

/*
** Reader structure
*/
typedef struct		s_pipel
{
	t_cmd			*cmd;
	int				pid;
	struct s_pipel	*previous;
	struct s_pipel	*next;
}					t_pipel;

typedef struct		s_fd
{
	int				op[2];
	int				np[2];
	int				sfd;
}					t_fd;

/*
** Builtin
*/

typedef struct		s_opt
{
	char			*opt;
	char			*value;
	struct s_opt	*next;
}					t_opt;

typedef struct		s_options
{
	int			ret;
	t_opt		*opts;
	size_t		last;
}					t_options;

typedef struct		s_builtin
{
	char	*name;
	int		(*func)();
}					t_builtin;

/*
** Jobs linked list
*/

typedef struct		s_jobs_lst
{
	int					job_number;
	int					pid;
	char				current;
	int					state;
	char				*command;
	int					foreground;
	t_pipel				*pipeline;
	struct termios		tmodes;
	struct s_jobs_lst	*prev;
	struct s_jobs_lst	*next;
}					t_jobs_lst;

typedef struct		s_jobs
{
	size_t			len;
	size_t			index;
	t_jobs_lst		*lst;
	t_jobs_lst		*last_job;
	t_jobs_lst		*plus;
	t_jobs_lst		*minus;
}					t_jobs;

/*
** Hashtable structure
*/
typedef struct		s_hashval
{
	char	*key;
	char	*value;
	size_t	occurence;
}					t_hashval;

typedef struct		s_hashtable
{
	int			size;
	t_hashval	*table;
}					t_hashtable;

/*
** History structure
*/
typedef struct		s_histo_lst
{
	char				*str;
	size_t				len;
	size_t				index;
	struct s_histo_lst	*prev;
	struct s_histo_lst	*next;
}					t_histo_lst;

typedef struct		s_history
{
	t_histo_lst			*lst;
	t_histo_lst			*first_element;
	size_t				pos;
	size_t				size;
	size_t				index;
	size_t				histsize;
	char				*first_command;
}					t_history;

/*
** Main shell structure
*/
typedef struct		s_shell
{
	t_var			*vars;
	t_alias			*alias;
	t_lexer			lexer;
	t_anode			*ast;
	t_hashtable		bin_ht;
	t_jobs			jobs;
	t_history		history;
	t_cmd			*current_cmd;
	t_pipel			*current_pipel;
	pid_t			pid;
	int				pgrp;
	int				able_termcaps;
	int				stopped_jobs;
	struct termios	prev_term;
	char			*ps1;
}					t_shell;

#endif
