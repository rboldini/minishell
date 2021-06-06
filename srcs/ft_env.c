#include "../includes/minishell.h"

char	**duplicate_env(char **env)
{
	char	**dup;
	int		i;
	int		k;

	i = 0;
	k = 0;
	dup = malloc(sizeof(char *));
	while (env[k] != 0)
	{
		dup[i] = ft_strdup(env[k]);
		i++;
		k++;
	}
	dup[i] = 0;		//se non lo null termini dio cantante
	return (dup);
}

t_env	*ft_parse_env(char **env)
{
	char	**tmp;
	int		i;
	int k;
	t_env	*parsed_env;
	t_env 	*tempo;

	tempo = malloc(sizeof(t_env));
	parsed_env = tempo;
	tmp = duplicate_env(env);
	k = 0;
	while (tmp[k])
	{
		i = 0;
		while (tmp[k][i] != '=' && tmp[k][i])
			i++;
		tmp[k][i] = 0;
		parsed_env->env_name = ft_strdup(tmp[k]);
		tmp[k] += i + 1;
		parsed_env->env_value = ft_strdup(tmp[k]);
		parsed_env->exp = 1;
		k++;
		if (tmp[k])
		{
			parsed_env->next_env = malloc(sizeof(t_env));
			parsed_env = parsed_env->next_env;
		}
		else
		{
			parsed_env->next_env = NULL;
		}
	}
	//ft_free_matrix(tmp);
	return (tempo);
}

t_env	*init_env(char **env)
{
	t_env	*enva;

	//env = malloc(sizeof(env));
	enva = ft_parse_env(env);
	return (enva);
}

void	ft_env(t_env *env)
{
	t_env	*tmp;
	
	tmp = env;
	while (tmp)
	{
		if (tmp->exp == 1)
		{
			ft_printf_fd(1, "%s", tmp->env_name);
			ft_printf_fd(1, "=");
			ft_printf_fd(1, "%s", tmp->env_value);
			ft_printf_fd(1, "\n");
		}
		tmp = tmp->next_env;
	}
}