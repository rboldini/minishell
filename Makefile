#Name
NAME =			minishell

#Compiler
CC = 			gcc
CFLAGS = 		-Wall -Wextra -Werror -g

#Norm
NORM =			norminette

#Shell
MKDIR =			mkdir -p
RM =			rm -rf

#Directories
SRCDIR = 		./srcs/*
OBJDIR =  		./objs/*
INCDIR = 		./includes

FILES =			main.c			\
				utils.c			\
				keyhook.c		\
				parser.c		\
				parser_utils.c	\
				parser_utils2.c	\
				parser_cmd.c	\
				parser_dollar.c	\
				parser_quote.c	\
				parser_token.c	\
				ft_echo.c		\
				ft_pwd.c		\
				command.c		\
				ft_env.c		\
				env_utils.c		\
				executor.c		\
				executor_utils.c\
				export_env.c	\
				special_keys.c	\
				ft_unset.c		\
				debug.c			\
				ft_cd.c			\
				check_ctrl.c	\
				ft_home_end.c	\
				runner.c		\
				ft_signal.c		\
				error.c			\
				d_redirect.c	\
				keyhook_utils.c	\
				special_keys_utils.c	\
				ft_exit.c		\
				forker.c		\
				forker_utils.c	\
				ft_cd_relative_and_absolute_paths.c	\
				env_utils2.c	\
				ft_export.c		\
				frame.c			\
				frame2.c		\
				asciimation.c	\
				ft_env2.c		

LIBFT_DIR =		libft

#Srcs
SRCS = 			$(foreach FILE, $(FILES), $(shell find $(SRCDIR) -name $(FILE)))

#Objs
OBJS = 			$(patsubst $(SRCDIR)/%, $(OBJDIR)/%, $(SRCS:.c=.o))

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(MKDIR) $(@D)
	@$(CC) $(CFLAGS) -I $(INCDIR) -c -o $@ $<

all: $(NAME)

$(NAME): libft printf $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_DIR)/libft.a ./ft_printf_fd/ft_printf_fd.a -o $(NAME)
	@clear -c

libft:
	@make -s bonus --quiet -C $(LIBFT_DIR)

printf:
	@make -s -C ./ft_printf_fd

norminette:
	@$(NORM)

clean:
	@$(RM) $(OBJDIR) $(OBJS)
	@make clean --quiet -C $(LIBFT_DIR)
	@make fclean --quiet -C ./ft_printf_fd

fclean: clean
	@$(RM) $(NAME)
	@make fclean --quiet -C $(LIBFT_DIR)
	@make fclean --quiet -C ./ft_printf_fd

run:
	@clear -c
	@make clean --quiet
	@./minishell

re: fclean all

.PHONY: all norminette libft clean fclean run re
