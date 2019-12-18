/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 17:28:10 by frossiny          #+#    #+#             */
/*   Updated: 2019/12/10 16:36:34 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	write_buf(char buf[], t_printf_state *s)
{
	int c;

	c = s->index;
	write(s->fd, buf, c);
	buf[0] = '\0';
	s->index = 0;
	return (c);
}

static size_t	write_arg(char buf[], t_printf_state *s)
{
	size_t	str_len;

	if (!s->arg || s->arg->str == NULL)
		return (s->index);
	str_len = ft_strlen(s->arg->str);
	if (s->arg->type == 'c' && s->arg->data.c == 0)
	{
		s->c += write_buf(buf, s);
		s->c += write(s->fd, s->arg->str,
			s->arg->width == 0 ? 1 : s->arg->width);
		return (s->index);
	}
	if (str_len >= BUFF_SIZE)
	{
		s->c += write_buf(buf, s);
		s->c += write(s->fd, s->arg->str, str_len);
		return (s->index);
	}
	if (s->index + ft_strlen(s->arg->str) >= BUFF_SIZE)
		s->c += write_buf(buf, s);
	ft_strcat(buf + s->index, s->arg->str);
	return ((s->index = ft_strlen(buf)));
}

static size_t	write_end(char buf[], char *format, t_printf_state *s)
{
	if (ft_strlen(buf) > 0)
		s->c += write_buf(buf, s);
	write(s->fd, format, ft_strlen(format));
	return (s->c + ft_strlen(format));
}

size_t			write_all(int fd, char *format, t_arg *alst)
{
	t_printf_state	s;
	char			buf[BUFF_SIZE + 1];
	int				i;

	i = 0;
	s.fd = fd;
	s.arg = alst;
	s.index = 0;
	s.c = 0;
	buf[0] = '\0';
	while (format[i])
		if (s.arg)
		{
			ft_strncat(buf, format + i, s.arg->index - i);
			s.index += s.arg->index - i;
			buf[s.index] = '\0';
			s.index = write_arg(buf, &s);
			i = s.arg->end + 1;
			s.arg = s.arg->next;
		}
		else
			return (write_end(buf, format + i, &s));
	s.c += write_buf(buf, &s);
	return (s.c);
}
