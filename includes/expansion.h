/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 17:24:02 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/01 16:32:18 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include <stdlib.h>
# include "structs.h"

typedef struct	s_expansion
{
	size_t	i;
	size_t	li;
	char	isquote;
	char	*str;
	char	*new;
}				t_expansion;

int				expand(t_token *tokens);
int				exp_remove_quotes(t_expansion *e);
int				handle_home(t_token *token, t_var *vars);

char			*strjoin_escape(char *s1, char *s2);
char			*strdup_escape(char *str);

#endif
