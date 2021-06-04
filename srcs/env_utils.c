#include "../includes/minishell.h"

void ft_free_matrix(char **matrix)
{
	int i;

	i = 0;
	while(matrix[i])
	{
		free(matrix[i]);
		matrix[i] = NULL;
		i++;
	}
	free(matrix);
	matrix = NULL;
}

void ft_free_env(t_env *env)
{
	t_env *tmp;

	while(env)
	{
		free(env->env_name)
		free(env->env_value)
		env = env->next_env;
	}
	free(tmp);
	tmp = NULL;
}

void ft_addback_env(t_env **env, t_env *new_env)
{
	t_env *tmp;

	tmp = *env;
	if(*env == NULL)
	{
		*env = new_env;
		(*env)->next_env = NULL;
	}
	while(tmp->next_env)
		tmp = tmp->next_env;
	tmp->next_env = new_env;
}

t_env *create_new_env(char *env)
{
	int i;

	i = 1;
	while(env[i] != '=')
		i++;
	env[i] = 0;
	//to_do with stefano
}

void edit_env(t_env **env,char *name, char *new_value)
{
	t_env *tmp;

	tmp = *env;
	while(tmp)
	{
		if(!ft_strcmp(tmp->env_name, name))
		{
			free(tmp->env_value);
			tmp->env_value = ft_strdup(new_value);
		}
		else
			tmp = tmp->next_env;
	}
}