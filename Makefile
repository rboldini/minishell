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
SRCDIR = 		./srcs
OBJDIR =  		./objs
INCDIR = 		./includes

#Files
FILES =			main.c		\
				parser.c	\
				lexar.c		\
				ft_echo.c	\
				ft_pwd.c	\
				command.c

LIBFT_DIR =		libft

#Srcs
SRCS = 			$(foreach FILE, $(FILES), $(shell find $(SRCDIR) -name $(FILE)))

#Objs
OBJS = 			$(patsubst $(SRCDIR)/%, $(OBJDIR)/%, $(SRCS:.c=.o))

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(MKDIR) $(@D)
	@$(CC) $(CFLAGS) -I $(INCDIR) -c -o $@ $<

all: $(NAME) run

$(NAME): libft $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_DIR)/libft.a -o $(NAME)

libft:
	@make -s bonus --quiet -C $(LIBFT_DIR)

norminette:
	@$(NORM)

clean:
	@$(RM) $(OBJDIR) $(OBJS)
	@make clean --quiet -C $(LIBFT_DIR)

fclean: clean
	@$(RM) $(NAME)
	@make fclean --quiet -C $(LIBFT_DIR)

run:
	@clear -c
	@./minishell

re: fclean all

.PHONY: all norminette libft clean fclean run re