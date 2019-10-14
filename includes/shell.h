/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 11:59:10 by frossiny          #+#    #+#             */
/*   Updated: 2019/08/13 12:37:36 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <stdlib.h>
# include <termios.h>

# include "lexer.h"
# include "ast.h"
# include "parser.h"
# include "termcaps.h"
# include "builtins.h"
# include "hashtable.h"
# include "env.h"

# define MAX_HISTORY	30
# define HT_SIZE		150

typedef struct		s_shell
{
	t_env			*env;
	t_lexer			lexer;
	t_anode			*ast;
	t_hashtable		bin_ht;
	t_history		history;
	struct termios	prev_term;
	int				able_termcaps : 1;
}					t_shell;

extern t_cursor_pos	g_pos;
extern int			g_child;
extern int			g_clear_buffer;
extern int			g_ignore_signals;
extern int			g_return;

int					shell(t_shell *shell);
void				prompt(void);
int					prompt_len(void);
int					check_quotes(char *str, char c);

int					lex(char *s, t_lexer *lexer);
int					is_escaped(char *s, size_t index, int endquote);
t_ex_token			lexer_search(const char *s);
void				destroy_lexer(t_lexer *lexer);
t_token				*push_token(t_token *list, t_token *new);
t_token				*create_token(t_lexer *lexer, char *content,
								size_t len, t_token_type type);
void				destroy_tokens(t_token *token);
int					is_word_token(t_token *token);

int					build_ast(t_shell *shell, t_anode **ast);
int					build_args(t_cmd *cmd, t_env *env);
void				destroy_ast(t_shell *shell);

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

void				ht_put(t_shell *shell, char *key, char *value);
char				*ht_get(t_shell *shell, char *key);
int					ht_exists(t_shell *shell, char *key);
int					ht_delone(char *key, t_shell *shell);
void				ht_delete(t_shell *shell);
int					ht_hash(size_t size, char *key);
int					ht_create(t_shell *shell, size_t size);

char				**dup_argv(int argc, char **args, char ***argv);
int					replace_vars(t_token *curr, t_env *env);
size_t				get_var_size(char *key);
int					handle_home(t_token *token, t_env *env);
char				*strjoin_escape(char *s1, char *s2);
char				*strdup_escape(char *str);

char				*get_exe(t_shell *shell, char *name, int verbose);
int					is_exe(t_shell *shell, char *name, int verbose);
int					execute(t_cmd *cmd, t_shell *shell);
int					execute_env(t_cmd *cmd, t_env *env, t_shell *shell);
int					handle_builtin(t_cmd *cmd, t_shell *shell);
t_builtin			get_builtin(char *name);
int					is_builtin(char *name);
int					b_env(t_cmd *cmd, t_shell *shell);
int					b_setenv(t_cmd *cmd, t_shell *shell);
int					b_unsetenv(t_cmd *cmd, t_shell *shell);
int					b_exit(t_cmd *cmd, t_shell *shell);
int					b_cd(t_cmd *cmd, t_shell *shell);
int					b_echo(t_cmd *cmd, t_shell *shell);
void				restore_fd(int fd[]);

void				register_signals(void);
void				unregister_signals(void);
int					display_signal(int sigid);

t_childs			*child_add(t_childs **childs, int pid);
void				child_del(t_childs *childs);

/*
**	utils.c
*/
int					is_local_exe(char *name);
int					is_relative_path(char *name);
char				*format_path_exe(char *dir, char *file);
int					cd_is_dir(char *file, char *name);
int					can_execute(char *path, t_shell *shell);
void				copy_tab(int op[], int np[]);

void				inexistant(char *name);
void				not_found(char *name);
int					permission_denied(char *name);
void				no_user(char *name);
int					cd_exists(char *file, char *name);
void				env_invalid_arg(int *argc, char ***argv);
int					parse_error(const char *str, size_t len, int ret);
int					is_directory_err(char *name);

int					termcaps_init(struct termios *prev_term);
void				restore_shell(struct termios prev_term);
void				free_termcaps(t_shell *shell);
int					get_input(int fd, char **dest, t_shell *shell);
int					get_pos(t_cursor_pos *pos);
int					read_all(int fd, char **dest);
int					memset_all(char **str, t_history *history,
												t_cursor_pos *pos);
int					is_special(const char *s);
int					execute_termcaps(char *buf, char **str,
									t_cursor_pos *pos, t_shell *shell);
void				end_reading(char **dest, char *buf, t_cursor_pos *pos,
															t_shell *shell);
void				resize(int sig);

int					memset_pos(t_cursor_pos *pos);
void				move_cursor(int x, int y);
void				final_position(t_cursor_pos *pos);
void				reprint(char *str, t_cursor_pos *pos, int cursor_pos);
void				visual_delete(char **str, t_cursor_pos *pos);
void				visual_replace(char **str, char *buf, t_cursor_pos *pos);
void				visual_print(char *str, t_cursor_pos *pos);
void				history_search_delete(char **str, t_cursor_pos *pos,
														t_history *histo);
void				history_search_replace(char **str, char *buf,
								t_cursor_pos *pos, t_history *histo);

void				free_history(t_history *history);
void				memset_history(t_history *history);
t_history			get_history(void);
void				overwrite_history(t_histo_lst *histo);
t_histo_lst			*new_link(char *str);
void				add_to_history(char *str, t_history *history);

void				termcaps_completion(char **str, t_cursor_pos *pos,
														t_shell *shell);
void				termcaps_up(char **str, t_cursor_pos *pos,
														t_shell *shell);
void				termcaps_down(char **str, t_cursor_pos *pos,
														t_shell *shell);
void				termcaps_left_word(char **str, t_cursor_pos *pos,
														t_shell *shell);
void				termcaps_right_word(char **str, t_cursor_pos *pos,
														t_shell *shell);
void				termcaps_left(char **str, t_cursor_pos *pos,
														t_shell *shell);
void				termcaps_right(char **str, t_cursor_pos *pos,
														t_shell *shell);
void				termcaps_delete(char **str, t_cursor_pos *pos,
														t_shell *shell);
void				termcaps_delete_right(char **str, t_cursor_pos *pos,
														t_shell *shell);
void				termcaps_history_next(char **str, t_cursor_pos *pos,
														t_shell *shell);
void				termcaps_history_prev(char **str, t_cursor_pos *pos,
														t_shell *shell);
void				termcaps_history_search(char **str, t_cursor_pos *pos
														, t_shell *shell);
void				termcaps_home(char **str, t_cursor_pos *pos,
														t_shell *shell);
void				termcaps_end(char **str, t_cursor_pos *pos,
														t_shell *shell);
void				termcaps_visual_mode(char **str, t_cursor_pos *pos,
														t_shell *shell);
void				termcaps_visual_paste(char **str, t_cursor_pos *pos,
														t_shell *shell);
void				termcaps_visual_cut(char **str, t_cursor_pos *pos,
														t_shell *shell);
void				termcaps_visual_copy(char **str, t_cursor_pos *pos,
														t_shell *shell);

int					complete_files(t_compl_info *ci, t_shell *shell);
void				include_word(char *word, char **str, t_cursor_pos *pos);
int					complete_path(t_compl_info *ci, t_shell *shell);
char				*get_tilde(char *word, t_env *env);
char				*get_file_start(char *word);

#endif
