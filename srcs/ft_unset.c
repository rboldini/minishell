#include "../includes/minishell.h"

void	ft_unset(t_env *env, int ac, char **av)
{
	t_env *tmp;
	int i;

	i = 1;
	tmp = env;

	while(i < ac)
	{
		if(check_existing_env(env, av[i]))
		{
			tmp->exp = 0;
			return ;
		}
		i++;
	}
}