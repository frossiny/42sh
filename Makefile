# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/03 14:37:18 by vsaltel           #+#    #+#              #
#    Updated: 2019/10/16 13:47:03 by frossiny         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	gcc -g3 #-fsanitize=address
#CFLAGS	+=	-Wall -Werror -Wextra

SHELL	=	bash

NAME 	=	42sh
LIBFT	=	libft
SRCDIR	=	srcs
INCDIR	=	includes
OBJDIR	=	objs
FILES 	=	main.c									\
			shell.c									\
			prompt.c								\
			termcaps/read_input.c					\
			termcaps/read_utils.c					\
			termcaps/termcaps.c						\
			termcaps/initialization.c				\
			termcaps/set_position.c					\
			termcaps/set_position_utils.c			\
			termcaps/completion/t_completion.c		\
			termcaps/completion/files.c				\
			termcaps/completion/path.c				\
			termcaps/completion/include_word.c		\
			termcaps/completion/get_tilde.c			\
			termcaps/completion/get_file_start.c	\
			termcaps/t_up.c							\
			termcaps/t_down.c						\
			termcaps/t_history_next.c				\
			termcaps/t_history_prev.c				\
			termcaps/t_history_search.c				\
			termcaps/t_left_word.c					\
			termcaps/t_right_word.c					\
			termcaps/t_left.c						\
			termcaps/t_right.c						\
			termcaps/t_delete.c						\
			termcaps/t_delete_right.c				\
			termcaps/t_home.c						\
			termcaps/t_end.c						\
			termcaps/t_visual_mode.c				\
			termcaps/t_visual_cut.c					\
			termcaps/t_visual_paste.c				\
			termcaps/t_visual_copy.c				\
			termcaps/history.c						\
			termcaps/history_utils.c				\
			termcaps/signal.c						\
			lexer/lexer.c							\
			lexer/is_escaped.c						\
			lexer/is_word_token.c					\
			lexer/lexer_free.c						\
			lexer/lexer_search.c					\
			lexer/create_token.c					\
			lexer/push_token.c						\
			lexer/replace_token.c					\
			lexer/update_state.c					\
			lexer/parse_error.c						\
			lexer/states/general.c					\
			lexer/states/quotes.c					\
			lexer/states/comment.c					\
			lexer/states/escaped.c					\
			lexer/states/operators.c				\
			parser/parser.c							\
			parser/pipe.c							\
			parser/pipeline.c						\
			parser/redirections.c					\
			parser/executables.c					\
			parser/here_doc.c						\
			parser/get_pipes_docs.c					\
			parser/exec_utils.c						\
			parser/child_add.c						\
			hashtable/ht_create.c					\
			hashtable/ht_hash.c						\
			hashtable/ht_delone.c					\
			hashtable/ht_delete.c					\
			hashtable/ht_put.c						\
			hashtable/ht_get.c						\
			hashtable/ht_exists.c					\
			ast/build_ast.c							\
			ast/create_node.c						\
			ast/build_args.c						\
			ast/redirections.c						\
			ast/destroy_ast.c						\
			ast/create_cmd.c						\
			builtins/builtins.c						\
			builtins/builtins_errors.c				\
			builtins/env.c							\
			builtins/setenv.c						\
			builtins/unsetenv.c						\
			builtins/exit.c							\
			builtins/cd.c							\
			builtins/echo.c							\
			builtins/export.c						\
			utils/dup_argv.c						\
			utils/display_signal.c					\
			utils/get_var_size.c					\
			utils/str_escape.c						\
			utils/copy_tab.c						\
			variables/var_build_env.c				\
			variables/var_delete.c					\
			variables/var_destroy.c					\
			variables/var_get.c						\
			variables/var_init.c					\
			variables/var_new.c						\
			variables/var_replace.c					\
			variables/var_set.c						\
			variables/var_display.c					\
			variables/var_disp_env.c				\
			signals.c								\
			errors.c								\
			utils.c									\
			expansion/variables.c					\
			expansion/tilde.c
SRCS	=	$(addprefix $(SRCDIR)/, $(FILES))
OBJS 	=	$(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
OBJSD 	=	$(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.d)

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

.PHONY: all clean fclean re norm $(LIBFT)

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -q -C $(LIBFT) || $(MAKE) -C $(LIBFT)
	@echo -e -n "\n${_BLUE}${_BOLD}[Create Executable] $(NAME)${_END}"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L./$(LIBFT) -lft -ltermcap
	@echo -e "\n${_GREEN}${_BOLD}$(NAME) done.${_END}"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	@echo -n -e "\r\033[K${_PURPLE}${BOLD}[${NAME}] Compiling $<${_END}"
	@$(CC) $(CFLAGS) -I $(INCDIR) -I $(LIBFT)/$(INCDIR) -MMD -o $@ -c $<

clean:
	@$(MAKE) -C $(LIBFT) clean
	@echo -e "${_RED}${_BOLD}Cleaning obj files...${_END}"
	@rm -f $(OBJS)
	@rm -f $(OBJSD)

fclean: clean
	@$(MAKE) -C $(LIBFT) fclean
	@echo -e "${_RED}${_BOLD}Cleaning project...${_END}"
	@rm -f $(NAME)

re: fclean
	@$(MAKE)

norm:
	@norminette $(INCDIR) $(SRCDIR) | grep "Warning\|Error" || true
	@echo "Norm done!"

-include $(OBJSD)
