# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/16 11:23:33 by frossiny          #+#    #+#              #
#    Updated: 2020/01/27 12:55:48 by lubenard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	clang
CFLAGS	+=	-Wall -Werror -Wextra -g3

SHELL	=	bash

NAME 	=	libft.a
SRCDIR	=	srcs
INCDIR	=	includes
OBJDIR	=	objs
FILES 	=	ft_2dstrnew.c						\
			ft_2dstrlen.c						\
			ft_2dstrdel.c						\
			ft_2dstrndel.c						\
			ft_expend_2dstr.c					\
			ft_retfree.c						\
			ft_memset.c							\
			ft_memalloc.c						\
			ft_memdel.c							\
			ft_memcpy.c							\
			ft_memccpy.c						\
			ft_memchr.c							\
			ft_memmove.c						\
			ft_memcmp.c							\
			ft_bzero.c							\
			ft_strlen.c							\
			ft_strdup.c							\
			ft_strndup.c						\
			ft_strcpy.c							\
			ft_strncpy.c						\
			ft_strlcpy.c						\
			ft_strcat.c							\
			ft_strncat.c						\
			ft_strlcat.c						\
			ft_strchr.c							\
			ft_strrchr.c						\
			ft_strstr.c							\
			ft_strnstr.c						\
			ft_strcmp.c							\
			ft_strncmp.c						\
			ft_strrev.c							\
			ft_strnew.c							\
			ft_strdel.c							\
			ft_strddel.c						\
			ft_strclr.c							\
			ft_striter.c						\
			ft_striteri.c						\
			ft_strmap.c							\
			ft_strmapi.c						\
			ft_strequ.c							\
			ft_strnequ.c						\
			ft_strsub.c							\
			ft_strjoin.c						\
			ft_strjoinf.c						\
			ft_strnjoin.c						\
			ft_strjoint.c						\
			ft_strjointf.c						\
			ft_strnfjoin.c						\
			ft_multifree.c						\
			ft_strtrim.c						\
			ft_strctrim.c						\
			ft_strsplit.c						\
			ft_strisalnum.c						\
			ft_strisdigit.c						\
			ft_strisascii.c						\
			ft_stradd.c							\
			ft_strnncmp.c						\
			ft_atoi.c							\
			ft_itoa.c							\
			ft_islower.c						\
			ft_isupper.c						\
			ft_isalpha.c						\
			ft_isdigit.c						\
			ft_isalnum.c						\
			ft_isascii.c						\
			ft_isprint.c						\
			ft_isspace.c						\
			ft_isnumeric.c						\
			ft_tolower.c						\
			ft_toupper.c						\
			ft_putchar.c						\
			ft_putstr.c							\
			ft_putnstr.c						\
			ft_putendl.c						\
			ft_putnbr.c							\
			ft_putchar_fd.c						\
			ft_putstr_fd.c						\
			ft_putnstr_fd.c						\
			ft_putendl_fd.c						\
			ft_putnbr_fd.c						\
			ft_lstnew.c							\
			ft_lstsort.c						\
			ft_lstdelone.c						\
			ft_lstadd.c							\
			ft_lstdel.c							\
			ft_lstdelstr.c						\
			ft_lstiter.c						\
			ft_lstmap.c							\
			ft_lstfold.c						\
			ft_freelst.c						\
			ft_strfjoin.c						\
			ft_strfdup.c						\
			ft_putstrtable.c					\
			ft_strpathfile.c					\
			ft_strcut.c							\
			ft_strfcut.c						\
			ft_lstend.c							\
			ft_lstsize.c						\
			ft_print_strlist.c					\
			get_next_line.c						\
			edit_string.c						\
			printf/ft_printf.c					\
			printf/display.c					\
			printf/arg_parser.c					\
			printf/size_parser.c				\
			printf/arg_filler.c					\
			printf/converter.c					\
			printf/utils.c						\
			printf/utils2.c						\
			printf/float_utils.c				\
			printf/converters/char.c			\
			printf/converters/ftoa.c			\
			printf/converters/integer.c			\
			printf/converters/pointer.c			\
			printf/converters/itoa_signed.c		\
			printf/converters/itoa_unsigned.c	\
			printf/converters/unknown.c
SRCS	=	$(addprefix $(SRCDIR)/, $(FILES))
OBJS	=	$(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
OBJSD	=	$(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.d)

##### Colors #####
_END=\x1b[0m
_BOLD=\x1b[1m
_UNDER=\x1b[4m
_REV=\x1b[7m
_GREY=\x1b[30m
_RED=\x1b[31m
_GREEN=\x1b[32m
_YELLOW=\x1b[33m
_BLUE=\x1b[34m
_PURPLE=\x1b[35m
_CYAN=\x1b[36m
_WHITE=\x1b[37m

.PHONY: all clean fclean re

.SILENT:

$(NAME): $(OBJS)
	@echo -e -n "\n${_BLUE}${_BOLD}[Linking] $(NAME)${_END}"
	@ar rcs $(NAME) $(OBJS)
	@echo -e -n "\n${_GREEN}${_BOLD}$(NAME) done.${_END}"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@[ -d $(OBJDIR) ] || mkdir -p $(OBJDIR)
	@[ -d $(OBJDIR)/printf ] || mkdir -p $(OBJDIR)/printf
	@[ -d $(OBJDIR)/printf/converters ] || mkdir -p $(OBJDIR)/printf/converters
	@echo -n -e "\r\033[K${_PURPLE}${BOLD}[${NAME}] Compiling $<${_END}"
	@$(CC) $(CFLAGS) -I $(INCDIR) -MMD -o $@ -c $<

all: $(NAME)

clean:
	@echo -e "${_RED}${_BOLD}Removing obj files...${_END}"
	@rm -f $(OBJS)
	@rm -f $(OBJSD)

fclean: clean
	@echo -e "${_RED}${_BOLD}Removing $(NAME)...${_END}"
	@rm -f $(NAME)
	@rm -rf $(OBJDIR)

re: fclean
	$(MAKE) $(NAME)

-include $(OBJSD)
