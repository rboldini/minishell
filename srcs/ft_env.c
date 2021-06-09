#include "../includes/minishell.h"

char	**duplicate_env(char **env)
{
	char	**dup;
	int		i;

	i = 0;
	while(env[i])
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
		parsed_env->env_value = ft_strdup(tmp[k] + i + 1);
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
	ft_free_matrix(tmp);
	return (tempo);
}

t_env	*init_env(char **env)
{
	t_env	*enva;

	enva = ft_parse_env(env);
	return (enva);
}

void	ft_env(t_env *env, int ac, char **av)
{
	t_env	*tmp;
	int i;
	char *str;
	int flag;
	
	(void)ac;
	i = 0;
	tmp = env;
	if(av[1])
	{
		str = ft_strdup(av[1]);
		while(str[i] != '=' && str[i])
		{
			i++;
			if(str[i] == '=')
				break;
			else if(!str[i])
				return ; 
		}
		str[i] = 0;
		if(check_existing_env(env, str))
			edit_env(&env, str, str + i);
		else
		{
			str[i] = '=';
			create_new_env(&env, str, 0);
		}
		flag = 1;
	}
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
	if(flag)
	{
			ft_printf_fd(1, "%s", str);
			ft_printf_fd(1, "=");
			ft_printf_fd(1, "%s", str + 1);
			ft_printf_fd(1, "\n");
	}
}