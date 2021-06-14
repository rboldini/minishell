#include "../includes/minishell.h"

void ft_print_env(t_env *env)
{
	while(env)
	{
		printf("%s", env->env_name);
		printf("=");
		printf("%s\n", env->env_value);
		env = env->next_env;
	}
}