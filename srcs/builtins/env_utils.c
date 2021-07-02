#include "../../includes/minishell.h"

t_env	*check_existing_env(t_env *env, char *name)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(name, tmp->env_name))
			return (tmp);
		else
			tmp = tmp->next_env;
	}
	return (NULL);
}

void	edit_env(t_env **env, char *name, char *new_value)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->env_name, name))
		{
			if (tmp->env_value)
				free(tmp->env_value);
			tmp->env_value = ft_strdup(new_value);
			break ;
		}
		else
			tmp = tmp->next_env;
	}
}

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

void	set_env(t_env **env, char *name)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->env_name, name))
			tmp->exp = 1;
		tmp = tmp->next_env;
	}
}

void	unset_env(t_env **env, char *name)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->env_name, name))
			tmp->exp = 0;
		tmp = tmp->next_env;
	}
}
