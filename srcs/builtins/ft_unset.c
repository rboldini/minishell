#include "../../includes/minishell.h"

void	ft_remove_env_node(t_env *env, char *name)
{
	t_env	*tmp;
	t_env	*prev;
	t_env	*next;
	t_env	*tempo;

	next = 0;
	prev = 0;
	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->env_name, name))
		{
			free(tmp->env_name);
			free(tmp->env_value);
			tempo = tmp;
			next = tmp->next_env;
			free(tempo);
			prev->next_env = next;
			return ;
		}
		prev = tmp;
		next = tmp->next_env;
		tmp = tmp->next_env;
	}
}

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
			ft_remove_env_node(*env, tmp->env_name);
		i++;
	}
}
