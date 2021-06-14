#include "../includes/minishell.h"

void ft_pwd(t_env *env)
{
	char *pwd;
	//char *test = malloc(sizeof(char) * 4096);

	pwd = ft_getenv(env, "PWD");
	//test = getcwd(test, 4096);
	ft_printf_fd(1, "%s\n", pwd);
}
