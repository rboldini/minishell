all:
	@make -s --makefile=./run_it
	@echo "\033[0;35mClosing Minishell..."

run: all

clean:
	@make -s --makefile=./run_it clean
	@echo "\033[0;35mCleaning Minishell..."

fclean:
	@make -s --makefile=./run_it fclean
	@echo "\033[0;35mFully cleaning Minishell..."

re:
	@make -s --makefile=./run_it fclean
	@echo "\033[0;35mRe-compiling Minishell..."

.PHONY: all run clean fclean re
