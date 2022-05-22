SRCS = 	minishell.c \
		srcs_exec/exec_utils.c			\
		srcs_exec/exec_utils_2.c		\
		srcs_exec/exec_utils_3.c		\
		srcs_exec/envp.c				\
		srcs_exec/envp_2.c				\
		srcs_exec/envp_3.c				\
		srcs_exec/pipe.c				\
		srcs_exec/exec.c				\
		srcs_exec/get_pwd.c				\
		srcs_exec/l_split.c				\
		srcs_exec/ft_atoi_and_itoa.c	\
		srcs_parse/parse_split.c		\
		srcs_parse/parse_utils.c		\
		srcs_parse/parse_utils_2.c		\
		srcs_parse/parse_utils_3.c		\
		srcs_parse/parse_utils_4.c		\
		srcs_parse/parse_utils_5.c		\
		srcs_parse/parse_heredoc.c		\
		srcs_parse/parse_trim.c			\
		srcs_parse/parse_rpl_arg.c		\
		srcs_parse/signals.c 			\
		srcs_parse/parse.c				\
		srcs_parse/parse_split_utils.c	\
		builtins/check_bt.c				\
		builtins/export.c				\
		builtins/export_2.c				\
		builtins/export_only.c			\
		builtins/env_only.c				\
		builtins/unset.c				\
		builtins/pwd.c					\
		builtins/echo.c					\
		builtins/exit.c					\
		builtins/cd.c					\
		builtins/cd_2.c					\


OBJS = ${SRCS:.c=.o}

NAME = minishell

READLINE_LIB	=	-L$(shell brew --prefix readline)/lib
READLINE_INC	=	-I$(shell brew --prefix readline)/include

CC = gcc
CFLAGS = -Wall -Werror -Wextra #-fsanitize=address -g3

RM = rm -rf

%.o: %.c includes/minishell.h includes/minishell_exec.h Makefile
	$(CC) ${CFLAGS} ${READLINE_INC} -c -o $@ $<

all: ${NAME}

${NAME}: ${OBJS}
	$(CC) ${CFLAGS} -lreadline ${READLINE_LIB} ${READLINE_INC} $(OBJS) -o $(NAME)

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
