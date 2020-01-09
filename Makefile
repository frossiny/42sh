# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/19 17:28:40 by vsaltel           #+#    #+#              #
#    Updated: 2020/01/09 14:29:59 by vsaltel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	gcc -g3 -fsanitize=address
CFLAGS	+=	-Wall -Wextra #-Werror

SHELL	=	bash

#Tests related variables
TARGS	=
ifdef FILTER
	TARGS += --filter ${FILTER}
endif
ifdef SHOW
	TARGS += --show-success
endif

NAME 	=	42sh
LIBFT	=	libft
SRCDIR	=	srcs
INCDIR	=	includes
OBJDIR	=	objs
FILES	=	shell.c											\
			main.c											\
			prompt.c										\
			signals.c										\
			errors.c										\
			utils.c											\
			alias/alias_new.c								\
			alias/alias_get.c								\
			alias/alias_display.c							\
			alias/alias_free.c								\
			alias/alias_resolve.c							\
			alias/alias_exec.c								\
			alias/alias_utils.c								\
			ast/ast_build.c									\
			ast/create_node.c								\
			ast/ast_build_args.c							\
			ast/redirections.c								\
			ast/ast_destroy.c								\
			ast/create_cmd.c								\
			ast/ast_is_bg.c									\
			builtins/alias.c								\
			builtins/unalias.c								\
			builtins/type/type.c							\
			builtins/type/type_utils.c						\
			builtins/type/type_search.c						\
			builtins/builtins.c								\
			builtins/builtins_errors.c						\
			builtins/set.c									\
			builtins/unset.c								\
			builtins/exit.c									\
			builtins/echo.c									\
			builtins/export.c								\
			builtins/fg.c									\
			builtins/jobs/jobs.c							\
			builtins/jobs/build_options.c					\
			builtins/cd/build_path.c						\
			builtins/cd/cd.c								\
			builtins/history/history.c						\
			builtins/history/history_options.c				\
			builtins/history/history_utils.c				\
			builtins/hash.c									\
			builtins/options/opt_parse.c					\
			builtins/options/opt_add.c						\
			builtins/options/opt_get.c						\
			builtins/options/opt_free.c			 			\
			execution/exec_all.c							\
			execution/exec_redirections.c					\
			execution/exec_command.c						\
			execution/exec_specials.c						\
			execution/exec_here_doc.c						\
			execution/exec_fork_builtin.c					\
			execution/exec_utils.c							\
			execution/pipes/exec_pipes.c					\
			execution/pipes/exec_pipe_builtin.c				\
			execution/pipes/exec_pipe_cmd.c					\
			execution/pipes/exec_pipeline.c					\
			execution/pipes/exec_pipeline_alloc.c			\
			execution/pipes/exec_del_pipeline.c				\
			execution/pipes/exec_end_pipes.c				\
			execution/pipes/exec_get_pipes_docs.c			\
			execution/pipes/exec_is_pipe_bg.c				\
			execution/exec_child_add.c						\
			execution/exec_assign_vars.c					\
			expansion/tilde.c								\
			expansion/expansion.c							\
			expansion/exp_join.c							\
			expansion/exp_set_struct.c						\
			expansion/exp_remove_quotes.c					\
			expansion/exp_del_empty_tokens.c				\
			expansion/variables/exp_variables.c				\
			expansion/variables/exp_get_varname.c			\
			expansion/variables/exp_simple_var.c			\
			expansion/variables/exp_parameter.c				\
			expansion/variables/exp_parameter_parse.c		\
			expansion/variables/exp_par_len.c				\
			expansion/variables/exp_par_colon.c				\
			expansion/variables/exp_par_colon_op.c			\
			expansion/variables/exp_get_var.c				\
			expansion/variables/exp_get_word.c				\
			expansion/variables/exp_del_pattern.c			\
			expansion/variables/exp_tok_clean.c				\
			expansion/arithmetic/comp.c						\
			expansion/arithmetic/convert_base.c				\
			expansion/arithmetic/eval.c						\
			expansion/arithmetic/eval_expr.c				\
			expansion/arithmetic/eval_test.c				\
			expansion/arithmetic/ft_ato.c					\
			expansion/arithmetic/lexer.c					\
			expansion/arithmetic/op.c						\
			expansion/arithmetic/parser.c					\
			expansion/arithmetic/sep_less.c					\
			expansion/arithmetic/tools.c					\
			expansion/arithmetic/arithmetic.c				\
			expansion/globbing/globbing.c					\
			expansion/globbing/path.c						\
			expansion/globbing/complete.c					\
			expansion/globbing/wildcards.c					\
			expansion/globbing/globbing_utils.c				\
			expansion/globbing/token_utils.c				\
			expansion/globbing/utils.c						\
			hashtable/ht_create.c							\
			hashtable/ht_hash.c								\
			hashtable/ht_delone.c							\
			hashtable/ht_delete.c							\
			hashtable/ht_put.c								\
			hashtable/ht_get.c								\
			hashtable/ht_exists.c							\
			history/history.c								\
			history/history_utils.c							\
			history/histo_expansion.c						\
			history/histo_exp_utils.c						\
			jobcontrol/job_new.c							\
			jobcontrol/job_free.c							\
			jobcontrol/job_delete.c							\
			jobcontrol/job_destroy_all.c					\
			jobcontrol/job_check_status.c					\
			jobcontrol/job_get_command.c					\
			jobcontrol/job_search.c							\
			jobcontrol/job_can_exit.c						\
			lexer/lexer.c									\
			lexer/lex_build.c								\
			lexer/lex_free.c								\
			lexer/lex_search.c								\
			lexer/lex_update_state.c						\
			lexer/lex_is_expansion.c						\
			lexer/lex_exp_utils.c							\
			lexer/tokens/tok_new.c							\
			lexer/tokens/tok_create.c						\
			lexer/tokens/tok_destroy.c						\
			lexer/tokens/tok_is_word.c						\
			lexer/tokens/tok_is_redirection.c				\
			lexer/tokens/tok_push.c							\
			lexer/tokens/tok_replace.c						\
			lexer/tokens/tok_is_varexp.c					\
			lexer/tokens/tok_is_cmd_comp.c					\
			lexer/tokens/tok_free.c							\
			lexer/tokens/tok_to_input.c						\
			lexer/states/general.c							\
			lexer/states/quotes.c							\
			lexer/states/comment.c							\
			lexer/states/escaped.c							\
			lexer/states/operators.c						\
			lexer/states/expansions.c						\
			parser/parser.c									\
			parser/par_next.c								\
			parser/types/name.c								\
			parser/types/redirections.c						\
			parser/types/operators.c						\
			parser/types/jobs.c								\
			parser/types/semic.c							\
			parser/types/conditions.c						\
			termcaps/read_input.c							\
			termcaps/read_utils.c							\
			termcaps/termcaps.c								\
			termcaps/initialization.c						\
			termcaps/set_position.c							\
			termcaps/set_position_utils.c					\
			termcaps/t_up.c									\
			termcaps/t_down.c								\
			termcaps/t_history_next.c						\
			termcaps/t_history_prev.c						\
			termcaps/t_history_search.c						\
			termcaps/t_left_word.c							\
			termcaps/t_right_word.c							\
			termcaps/t_left.c								\
			termcaps/t_right.c								\
			termcaps/t_delete.c								\
			termcaps/t_delete_right.c						\
			termcaps/t_home.c								\
			termcaps/t_end.c								\
			termcaps/t_escape.c								\
			termcaps/t_visual_mode.c						\
			termcaps/t_visual_cut.c							\
			termcaps/t_visual_paste.c						\
			termcaps/t_visual_copy.c						\
			termcaps/signal.c								\
			termcaps/completion/t_completion.c				\
			termcaps/completion/lite_parser.c				\
			termcaps/completion/files.c						\
			termcaps/completion/cmd.c						\
			termcaps/completion/var.c						\
			termcaps/completion/disp_compl.c				\
			utils/is_escaped.c								\
			utils/dup_argv.c								\
			utils/display_signal.c							\
			utils/get_var_size.c							\
			utils/str_escape.c								\
			utils/copy_tab.c								\
			utils/42shrc.c									\
			utils/u_free_shell.c							\
			variables/var_build_env.c						\
			variables/var_delete.c							\
			variables/var_destroy.c							\
			variables/var_get.c								\
			variables/var_value.c							\
			variables/var_init.c							\
			variables/var_new.c								\
			variables/var_replace.c							\
			variables/var_set.c								\
			variables/var_display.c							\
			variables/var_disp_env.c						\
			variables/var_is_key_valid.c					\
			variables/var_merge.c							\
			variables/var_export.c

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

.PHONY: all clean fclean re norm tests $(LIBFT)

.SILENT:

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -q -C $(LIBFT) || $(MAKE) -j4 -C $(LIBFT)
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
	@rm -rf $(OBJDIR)
	@rm -rf $(NAME).dSYM
	@rm -rf /tmp/makefile_42sh

re: fclean
	@$(MAKE)

norm:
	@norminette $(INCDIR) $(SRCDIR) | grep "Warning\|Error" || true
	@echo "Norm done!"

check_error:
	@grep -rn "printf" srcs | grep -v "ft_"
	@grep -rn "stdio.h" srcs

valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all --suppressions="${PWD}/valgrind.supp" "${PWD}/${NAME}"

tests: all
	./tests/42ShellTester/42ShellTester.sh "$(PWD)/$(NAME)" ${TARGS}

pytest:
	python3 ./tests/python_test/err.py $(FILTER) ./tests/python_test/$(FILE)

-include $(OBJSD)
