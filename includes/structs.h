/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:23:53 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/04 14:28:16 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdlib.h>
# include <termios.h>

/*
** Alias structure
*/
typedef struct	s_alias
{
	char			*key;
	char			*value;
	struct s_alias	*next;
}				t_alias;

/*
** Variables structure
*/
typedef struct	s_var
{
	char			*key;
	char			*value;
	int				export;
	struct s_var	*next;
}				t_var;

/*
** Lexer structs
*/
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
	int			is_glob_sub;
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


/*
** AST structures
*/
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

/*
** Parser structure
*/
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

/*
** Builtin
*/

typedef struct	s_opt
{
	char			*opt;
	char			*value;
	struct s_opt	*next;
}				t_opt;

typedef struct	s_options
{
	int			ret;
	t_opt		*opts;
	size_t		last;
}				t_options;

typedef struct	s_builtin
{
	char	*name;
	int		(*func)();
}				t_builtin;

/*
** Hashtable structure
*/
typedef struct		s_hashval
{
	char	*key;
	char	*value;
}					t_hashval;

typedef struct		s_hashtable
{
	int			size;
	t_hashval	*table;
}					t_hashtable;

/*
** History structure
*/
typedef struct	s_histo_lst
{
	char				*str;
	size_t				len;
	struct s_histo_lst	*next;
}				t_histo_lst;

typedef struct	s_history
{
	t_histo_lst			*lst;
	size_t				pos;
	size_t				size;
	char				*first_command;
}				t_history;

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
	t_history		history;
	struct termios	prev_term;
}					t_shell;

#endif
