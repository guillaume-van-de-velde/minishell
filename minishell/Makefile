SRC_EXPORT			=	export.c complete_env.c

SRC_EXIT			=	exit.c exit_process.c

SRC_BUILTINS		=	${addprefix export/, ${SRC_EXPORT}} ${addprefix exit/, ${SRC_EXIT}} \
						cd.c echo.c env.c pwd.c unset.c

SRC_PIPELINE_STEPS	=	pipeline_steps.c end_of_pipeline.c

SRC_ANOTHER			=	another.c validate_command.c

SRC_EXECUTION		=	${addprefix builtins/, ${SRC_BUILTINS}} ${addprefix pipeline_steps/, ${SRC_PIPELINE_STEPS}} \
						${addprefix another/, ${SRC_ANOTHER}} execute_command.c execution.c for_dup.c \
						path.c pipe.c

SRC_ARRAY_METHODS	=	join_str_arr.c insert.c

SRC_HEREDOCS		=	heredocs.c heredocs_utils.c heredoc_child.c

SRC_IS_FUNCTIONS	=	is_functions_1.c is_functions_2.c is_functions_3.c

SRC_LINE_METHODS	=	dup_word.c env_var.c get_line_args.c

SRC_REDIRECTIONS	=	get_redirections.c get_redirections_utils.c heredoc.c

SRC_SYNTAX			=	check_parenthesis.c syntax_check.c utils.c

SRC_WILDCARDS		=	get_wildcard_matches.c utils.c wildcards.c

SRC_PARSING			=	${addprefix array_methods/, ${SRC_ARRAY_METHODS}} ${addprefix heredocs/, ${SRC_HEREDOCS}} \
						${addprefix is_functions/, ${SRC_IS_FUNCTIONS}} ${addprefix line_methods/, ${SRC_LINE_METHODS}} \
						${addprefix redirections/, ${SRC_REDIRECTIONS}} ${addprefix syntax/, ${SRC_SYNTAX}} \
						${addprefix wildcards/, ${SRC_WILDCARDS}} \
						ft_realloc.c parse_line.c parse_line_utils.c print_error.c close_heredoc_fds.c skip_pipelines.c \
						check_file_or_dir.c \

SRC					=	${addprefix execution/, ${SRC_EXECUTION}} ${addprefix parsing/, ${SRC_PARSING}} \
						main.c close_program.c signals.c singletons.c

SRCS				=	${addprefix sources/, ${SRC}}

OBJ					=	${addprefix binaries/, ${SRC}}

OBJS				=	$(OBJ:%.c=%.o)

INCLUDES_LIBFT		=	Libft/includes/gnl Libft/includes/libc Libft/includes/ptf

INCLUDES			=	${INCLUDES_LIBFT} includes/

HEADERS_MINISHELL	=	minishell.h parsing.h execution.h struct_minishell.h

HEADERS				=	${addprefix includes/, ${HEADERS_MINISHELL}}

NAME				=	minishell

CC					=	cc

CFLAGS				=	-g3 -Wall -Wextra -Werror

RM					=	rm -f

MAKEFLAGS			+=	--no-print-directory

binaries/%.o : sources/%.c ${HEADERS} Libft/libft.a Makefile | binaries
		@mkdir -p $(@D)
		$(CC) $(CFLAGS) -c $< -o $@ ${addprefix -I, ${INCLUDES}} 

${NAME}: ${OBJS}
	${CC} -o ${NAME} ${OBJS} -LLibft -lft -lreadline

all: $(NAME)

Libft/libft.a :
	@make -C Libft

binaries :
	@mkdir -p binaries/

bonus: all

clean:
		@$(RM) -r binaries
		@make clean -C Libft

fclean:	clean
		@${RM} $(NAME)
		@make fclean -C Libft

re:		fclean all

.PHONY: all bonus clean fclean re
