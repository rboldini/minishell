#include "../includes/minishell.h"

void	ft_free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		matrix[i] = NULL;
		i++;
	}
	free(matrix);
	matrix = NULL;
}

void	ft_free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		free(env->env_name);
		free(env->env_value);
		env = env->next_env;
	}
	free(tmp);
	tmp = NULL;
}

void	ft_addback_env(t_env **env, t_env *new_env)
{
	t_env	*tmp;

	tmp = *env;
	if (*env == NULL)
	{
		*env = new_env;
		(*env)->next_env = NULL;
	}
	while (tmp->next_env)
		tmp = tmp->next_env;
	tmp->next_env = new_env;
}

void create_new_env(t_env *env, char *raw_env, int export) //to_do with stefano (da fare funzione is_env che chiama create_new_env)
{
	int		i;
	t_env	*new;

	i = 1;
	while (raw_env[i] != '=')
		i++;
	raw_env[i] = 0;
	new = malloc(sizeof(t_env));
	new->env_name = ft_strdup(raw_env);
	raw_env += i + 1;
	new->env_value = ft_strdup(raw_env);
	new->exp = export;
	ft_addback_env(env, new);
}

void	edit_env(t_env **env,char *name, char *new_value)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->env_name, name))
		{
			free(tmp->env_value);
			tmp->env_value = new_value;
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
		if (ft_strcmp(tmp->env_name, name) == 0)
			return (tmp->env_value);
		tmp = tmp->next_env;
	}
	return (NULL);
}

void	unset_env(t_env *env, char* name)
{
	int		i;
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->env_name, name))
			tmp->exp = 0;
		tmp = tmp->next_env;
	}
}