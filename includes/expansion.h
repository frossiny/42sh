/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 17:24:02 by frossiny          #+#    #+#             */
/*   Updated: 2019/08/12 15:20:19 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include <stdlib.h>

typedef struct	s_expansion
{
	size_t	i;
	size_t	li;
	char	isquote;
	char	*str;
}				t_expansion;

#endif
