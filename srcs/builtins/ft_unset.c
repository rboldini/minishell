#include "../../includes/minishell.h"

void	ft_unset(t_env **env, int ac, char **av)
{
	t_env	*tmp;
	int		i;

	i = 1;
	tmp = *env;
	while (i < ac)
	{
		tmp = check_existing_env(*env, av[i]);
		if (tmp)
			tmp->exp = 0;
		i++;
	}
}
