#include "../includes/minishell.h"

char	**duplicate_env(char **env)
{
	char	**dup;
	int		i;
	char	**tmp;

	i = 0;
	dup = malloc(sizeof(char *));
	tmp = env;
	while (*tmp)
	{
		dup[i] = ft_strdup(*tmp);
		i++;
		(*tmp)++;
	}
	dup[i] = 0;
	return (dup);
}

t_env	*ft_parse_env(char **env)
{
	char	**tmp;
	int		i;
	t_env	*parsed_env;

	parsed_env = malloc(sizeof(t_env));
	tmp = duplicate_env(env);
	i = 0;
	while (*tmp)
	{
		
		while (*tmp[i] || *tmp[i] != '=')
			i++;
		*tmp[i] = 0;
		parsed_env->env_name = ft_strdup(*tmp);
		*tmp += i + 1;
		parsed_env->env_value = ft_strdup(*tmp);
		parsed_env->exp = 1;
		tmp++;
		if (*tmp)
		{
			parsed_env->next_env = malloc(sizeof(t_env));
			parsed_env = parsed_env->next_env;
		}
		else
			parsed_env->next_env = NULL;
	}
	ft_free_matrix(tmp);
	return (parsed_env);
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