/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 18:49:29 by vsaltel           #+#    #+#             */
/*   Updated: 2019/11/27 15:14:12 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMCAPS_H
# define TERMCAPS_H

# include "structs.h"

/*
**	x; 			position x dans le shell
**	y; 			position y dans le shell
**	x_min; 		position x apres le prompt dans le shell
**	x_max; 		position x du dernier char de la ligne
**	x_lastc; 	postion x du dernier char dans l'input
**	y_lastc; 	postion y du dernier char dans l'input
**	x_rel; 		postion x dans la string
**	y_min; 		position y initiale de la ligne du prompt dans le shell
**	y_max; 		position y de la derniere ligne affichable dans le shell
*/

typedef struct		s_cursor_pos
{
	char				*str;
	long				len_str;
	long				x;
	long				y;
	long				x_rel;
	long				x_min;
	long				x_max;
	long				y_min;
	long				y_max;
	char				*o_input;
	long				compl;
	size_t				opos;
	int					visual_mode : 1;
	long				v_beg;
	char				*v_str;
	int					search_mode;
	char				*s_str;
}					t_cursor_pos;

typedef struct		s_ex_caps
{
	const char			*content;
	size_t				size;
	void				(*func)();
}					t_ex_caps;

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
void				term_print(char *str);
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
void				termcaps_escape(char **str, t_cursor_pos *pos,
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

void				include_word(char *word, char **str, t_cursor_pos *pos);
char				*get_tilde(char *word, t_var *var);
char				*get_file_start(char *word);

#endif
