#include "../includes/minishell.h"

int	env_lst_size(t_env *env)
{
	t_env *tmp;
	int res;

	tmp = env;
	res = 0;
	while(tmp)
	{
		res++;
		tmp = tmp->next_env;
	}
	return (res);
}

void	ft_export_env(t_env *env, char *str)
{
	t_env	*tmp;
	int		i;
	char	*str_tmp;

	i = 0;
	tmp = env;
	str_tmp = ft_strdup(str);
	while (str_tmp[i])
	{
		if (str_tmp[i] == '=' || str_tmp[i] == 0)
		{
			str_tmp[i] = 0;
			while (tmp)
			{
				if(ft_strcmp(str, tmp->env_name) == 0)
				{
					edit_env(&env, tmp->env_name, str + 1);
					set_env(&env, str + 1);
					free(str_tmp);
					return ;
				}
				tmp = tmp->next_env;
			}
		}
		i++;
	}
	create_new_env(&env, str, 1);
	free(str_tmp);
}

void	ft_export(t_env *env, int ac, char **av)
{
	t_env	*tmp;
	int i;
	
	i = 1;
	tmp = env;
	if(ac < 2)
	{
		while (tmp)
		{
			if (tmp->exp == 1)
			{
				ft_printf_fd(1, "declare -x ");
				ft_printf_fd(1, "%s", tmp->env_name);
				ft_printf_fd(1, "=");
				ft_printf_fd(1, "%s", tmp->env_value);
				ft_printf_fd(1, "\n");
			}
			tmp = tmp->next_env;
		}
	}
	else
	{
		while(i < ac - 1)
			ft_export_env(env, av[i++]);
	}
}

char	**exported_env_matrix(t_env *env)
{
	int len;
	char **env_matrix;
	int i;
	t_env *tmp;
	char *temp;
	
	i = 0;
	tmp = env;
	len = env_lst_size(env);
	env_matrix = malloc(sizeof(char *) * len);
	while (tmp)
	{
		if (tmp->exp == 1)
		{
			temp = ft_strjoin(tmp->env_name, "=");
			env_matrix[i] = ft_strjoin(temp, tmp->env_value);
			free(temp);
			i++;
		}
		tmp = tmp->next_env;
	}
	return (env_matrix);
}