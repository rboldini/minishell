#include "../../includes/minishell.h"

char	*ft_getenv(t_env *env, char *name)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->env_name, name))
			return (tmp->env_value);
		tmp = tmp->next_env;
	}
	return (NULL);
}

void	ft_remove_env_node(t_env *node, char *name)
{
	t_env	*tmp;
	int 	first;

	first = 1;
	tmp = node;
	while (node)
	{
		if (!ft_strcmp(node->env_name, name))
		{
			free(node->env_name);
			free(node->env_value);
			if (first)
				g_shell->env = node->next_env;
			else
				tmp->next_env = node->next_env;
			free(node);
			return ;
		}
		first = 0;
		tmp = node;
		node = node->next_env;
	}
}

void	ft_remove_env_node_(t_env *env, char *name)
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

int	check_env_to_unset(t_env *element)
{
	if (!ft_strcmp(element->env_name, "PWD")
		|| !ft_strcmp(element->env_name, "OLDPWD"))
	{
		element->exp = 3;
		return (1);
	}
	return (0);
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
		{
			if (check_env_to_unset(tmp))
				;
			else
				ft_remove_env_node(*env, tmp->env_name);
		}
		i++;
	}
}
