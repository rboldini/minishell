#include "../../includes/minishell.h"

void ft_pwd()
{
	char *test;
	
	test = malloc(sizeof(char) * 4096);
	test = getcwd(test, 4096);
	ft_printf_fd(1, "%s\n", test);
	free(test);
}
