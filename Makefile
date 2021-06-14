#Name
NAME =			minishell

#Compiler
CC = 			gcc
CFLAGS = 		-Wall -Wextra -Werror -g -fsanitize=address

#Norm
NORM =			norminette

#Shell
MKDIR =			mkdir -p
RM =			rm -rf

#Directories
SRCDIR = 		./srcs
OBJDIR =  		./objs
INCDIR = 		./includes

FILES =			main.c			\
				keyhook.c		\
				parser.c		\
				ft_echo.c		\
				ft_pwd.c		\
				command.c		\
				ft_env.c		\
				env_utils.c		\
				executor.c		\
				export_env.c	\
				special_keys.c	\
				ft_unset.c		\
				debug.c			\
				ft_cd.c			\

LIBFT_DIR =		libft

#Srcs
SRCS = 			$(foreach FILE, $(FILES), $(shell find $(SRCDIR) -name $(FILE)))

#Objs
OBJS = 			$(patsubst $(SRCDIR)/%, $(OBJDIR)/%, $(SRCS:.c=.o))

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(MKDIR) $(@D)
	@$(CC) $(CFLAGS) -I $(INCDIR) -c -o $@ $<

all: $(NAME) run

$(NAME): libft printf $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_DIR)/libft.a ./ft_printf_fd/ft_printf_fd.a -o $(NAME)

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
	@./minishell

re: fclean all

.PHONY: all norminette libft clean fclean run re