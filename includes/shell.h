/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 11:59:10 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/14 18:36:01 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <stdlib.h>
# include <termios.h>

# include "structs.h"
# include "termcaps.h"
# include "variables.h"

# define MAX_HISTORY	30
# define HT_SIZE		150

extern t_shell		g_shell;
extern t_cursor_pos	g_pos;
extern int			g_child;
extern int			g_clear_buffer;
extern int			g_ignore_signals;
extern int			g_return;

int					shell();
void				prompt(void);
int					prompt_len(void);
int					check_quotes(char *str, char c);

int					parse(t_shell *shell, t_anode *ast);
int					execute_pipes(t_anode *node, t_shell *shell, t_anode **cn);
t_pipel				*build_pipeline(t_anode *node, t_shell *shell,
															t_anode **cn);
t_redirect			*parse_redirections(t_token *tok, int offset);
void				del_pipeline(t_pipel *pline);
int					handle_redirections(t_redirect *redir);
int					get_here_doc(t_redirect *redir, t_shell *shell);
void				apply_here_doc(t_redirect *redir);
void				close_here_docs(t_redirect *redir);
int					get_pipes_docs(t_shell *shell, t_pipel *pipes);

char				**dup_argv(int argc, char **args, char ***argv);
int					replace_vars(t_token *curr, t_var *vars);
size_t				get_var_size(char *key);
int					handle_home(t_token *token, t_var *vars);
char				*strjoin_escape(char *s1, char *s2);
char				*strdup_escape(char *str);

char				*get_exe(t_shell *shell, char *name, int verbose);
int					is_exe(t_shell *shell, char *name, int verbose);
int					execute(t_cmd *cmd, t_shell *shell);
void				restore_fd(int fd[]);

void				register_signals(void);
void				unregister_signals(void);
int					display_signal(int sigid);

t_childs			*child_add(t_childs **childs, int pid);
void				child_del(t_childs *childs);

#endif
