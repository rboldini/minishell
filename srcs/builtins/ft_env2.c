#include "../../includes/minishell.h"

char	**duplicate_env(char **env)
{
	char	**dup;
	int		i;

	i = 0;
	while (env[i])
		i++;
	dup = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		dup[i] = ft_strdup(env[i]);
		i++;
	}
	dup[i] = 0;
	return (dup);
}

void	fill_env_node(t_env *parsed_env, char **tmp, int *k)
{
	int	i;

	i = 0;
	while (tmp[*k][i] != '=' && tmp[*k][i])
		i++;
	tmp[*k][i] = 0;
	parsed_env->env_name = ft_strdup(tmp[*k]);
	parsed_env->env_value = ft_strdup(tmp[*k] + i + 1);
	parsed_env->exp = 1;
	(*k)++;
	if (tmp[*k])
	{
		parsed_env->next_env = malloc(sizeof(t_env));
		parsed_env = parsed_env->next_env;
	}
	else
		parsed_env->next_env = NULL;
}

t_env	*ft_parse_env(char **env)
{
	char	**tmp;
	int		k;
	t_env	*parsed_env;
	t_env	*tempo;

	tempo = malloc(sizeof(t_env));
	parsed_env = tempo;
	tmp = duplicate_env(env);
	k = 0;
	while (tmp[k])
		fill_env_node(parsed_env, tmp, &k);
	ft_free_matrix(tmp);
	return (tempo);
}

t_env	*init_env(char **env)
{
	t_env	*enva;

	enva = ft_parse_env(env);
	return (enva);
}
