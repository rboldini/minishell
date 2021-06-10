#include "../includes/minishell.h"

void	ft_unset(t_env *env, int ac, char **av)
{
	t_env *tmp;

	tmp = env;
	while(tmp)
	{
		if(!ft_strcmp(exp_name, tmp->env_name))
		{
			tmp->exp = 0;
			return ;
		}
		tmp = tmp->next_env;
	}
}