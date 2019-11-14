# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/03 14:37:18 by vsaltel           #+#    #+#              #
#    Updated: 2019/11/14 20:24:56 by alagroy-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	gcc #-g3 -fsanitize=address
CFLAGS	+=	-Wall -Werror -Wextra

SHELL	=	bash

NAME 	=	42sh
LIBFT	=	libft
SRCDIR	=	srcs
INCDIR	=	includes
OBJDIR	=	objs/
FILES 	=	main.c									\
			shell.c									\
			prompt.c								\
			signals.c								\
			errors.c								\
			utils.c									\
			ast/build_ast.c							\
			ast/create_node.c						\
			ast/build_args.c						\
			ast/redirections.c						\
			ast/destroy_ast.c						\
			ast/create_cmd.c						\
			builtins/builtins.c						\
			builtins/builtins_errors.c				\
			builtins/set.c							\
			builtins/unset.c						\
			builtins/exit.c							\
			builtins/cd.c							\
			builtins/echo.c							\
			builtins/export.c						\
			builtins/options/opt_parse.c			\
			builtins/options/opt_add.c				\
			builtins/options/opt_get.c				\
			builtins/options/opt_free.c			 	\
			expansion/variables.c					\
			expansion/tilde.c						\
			hashtable/ht_create.c					\
			hashtable/ht_hash.c						\
			hashtable/ht_delone.c					\
			hashtable/ht_delete.c					\
			hashtable/ht_put.c						\
			hashtable/ht_get.c						\
			hashtable/ht_exists.c					\
			lexer/lexer.c							\
			lexer/lex_free.c						\
			lexer/lex_search.c						\
			lexer/lex_update_state.c				\
			lexer/lex_is_expansion.c				\
			lexer/tokens/tok_create.c				\
			lexer/tokens/tok_destroy.c				\
			lexer/tokens/tok_is_word.c				\
			lexer/tokens/tok_is_redirection.c		\
			lexer/tokens/tok_push.c					\
			lexer/tokens/tok_replace.c				\
			lexer/tokens/tok_is_varexp.c			\
			lexer/states/general.c					\
			lexer/states/quotes.c					\
			lexer/states/comment.c					\
			lexer/states/escaped.c					\
			lexer/states/operators.c				\
			lexer/states/expansions.c				\
			parser/parser.c							\
			parser/par_next.c						\
			parser/types/name.c						\
			parser/types/redirections.c				\
			parser/types/operators.c				\
			parser/types/semic.c					\
			reader/reader.c							\
			reader/pipe.c							\
			reader/pipeline.c						\
			reader/redirections.c					\
			reader/executables.c					\
			reader/here_doc.c						\
			reader/get_pipes_docs.c					\
			reader/exec_utils.c						\
			reader/child_add.c						\
			termcaps/read_input.c					\
			termcaps/read_utils.c					\
			termcaps/termcaps.c						\
			termcaps/initialization.c				\
			termcaps/set_position.c					\
			termcaps/set_position_utils.c			\
			termcaps/completion/t_completion.c		\
			termcaps/completion/lite_parser.c		\
			termcaps/completion/files.c				\
			termcaps/completion/cmd.c				\
			termcaps/completion/var.c				\
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
			utils/is_escaped.c						\
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
			variables/var_is_key_valid.c			\
			expansion/arithmetic/comp.c				\
			expansion/arithmetic/convert_base.c		\
			expansion/arithmetic/eval.c				\
			expansion/arithmetic/eval_expr.c		\
			expansion/arithmetic/eval_test.c		\
			expansion/arithmetic/ft_ato.c			\
			expansion/arithmetic/lexer.c			\
			expansion/arithmetic/op.c				\
			expansion/arithmetic/parser.c			\
			expansion/arithmetic/sep_less.c			\
			expansion/arithmetic/tools.c			\
			expansion/arithmetic/arithmetic.c

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

$(NAME): $(OBJS) Makefile
	@$(MAKE) -q -C $(LIBFT) || $(MAKE) -C $(LIBFT)
	@echo -e -n "\n${_BLUE}${_BOLD}[Create Executable] $(NAME)${_END}"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L./$(LIBFT) -lft -ltermcap
	@echo -e "\n${_GREEN}${_BOLD}$(NAME) done.${_END}"

$(OBJDIR)/%.o: $(SRCDIR)/%.c Makefile
	@mkdir -p $(@D)
	@echo -n -e "\r\033[K${_PURPLE}${BOLD}[${NAME}] Compiling $<${_END}"
	@$(CC) $(CFLAGS) -I $(INCDIR) -I $(LIBFT)/$(INCDIR) -MMD -o $@ -c $<

clean:
	@$(MAKE) -C $(LIBFT) clean
	@echo -e "${_RED}${_BOLD}Cleaning obj files...${_END}"
	@rm -f $(OBJS)
	@rm -f $(OBJSD)
	@rm -Rf $(OBJDIR)

fclean: clean
	@$(MAKE) -C $(LIBFT) fclean
	@echo -e "${_RED}${_BOLD}Cleaning project...${_END}"
	@rm -f $(NAME)

re: fclean
	@$(MAKE)

norm:
	@norminette $(INCDIR) $(SRCDIR) | grep "Warning\|Error" || true
	@echo "Norm done!"

test:
	python3 err.py

-include $(OBJSD)
