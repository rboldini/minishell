#include "../../includes/minishell.h"

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

	tmp = env;
	while (tmp)
	{
		free(tmp->env_name);
		free(tmp->env_value);
		tmp = tmp->next_env;
	}
	free(env);
	env = NULL;
}

t_env	*check_existing_env(t_env *env, char *name) //torna un puntatore all' elemento combaciante
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

//to_do with stefano (da fare funzione is_env che chiama create_new_env)
void create_new_env(t_env **env, char *raw_env, int export)
{
	int		i;
	t_env	*new;
	char 	*tmp_raw;
	t_env	*check;

	i = 0;
	tmp_raw = ft_strdup(raw_env);
	while (tmp_raw[i] != '=')
		i++;
	tmp_raw[i] = '\0';
	check = check_existing_env(*env, tmp_raw);
	if(!check)
	{
		new = malloc(sizeof(t_env));
		new->env_name = ft_strdup(tmp_raw);
		new->env_value = ft_strdup(tmp_raw + i + 1);
		new->exp = export;
		new->next_env = 0;
		ft_addback_env(env, new);
		free(tmp_raw);
	}
	else
	{
		free(check->env_value);
		check->env_value = ft_strdup(raw_env + i + 1);
	}
}

void	edit_env(t_env **env,char *name, char *new_value)
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

void	set_env(t_env **env, char* name)
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

void	unset_env(t_env **env, char* name)
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
