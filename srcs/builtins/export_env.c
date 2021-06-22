#include "../../includes/minishell.h"

void	equal_notequal(t_env *env, char *str_tmp, int i, char *str)
{
	t_env *same_element;
	int equal;

	if(str_tmp[i] == '=')
		equal = 1;
	else if(str_tmp[i] == 0)
		equal = 2;
	str_tmp[i] = 0;
	if((same_element = check_existing_env(env, str_tmp)) != 0)
	{
		if(same_element->env_value != 0 && equal == 2)
		{
			set_env(&env, same_element->env_name);
		}
		else if(equal == 1)
		{
			edit_env(&env, same_element->env_name, str_tmp + i + 1);
			set_env(&env, same_element->env_name);
		}
	}
	else
		create_new_env(&env, str, equal);
}

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
	int		i;
	char	*str_tmp;

	i = 0;
	str_tmp = ft_strdup(str);
	while (str_tmp[i] || !str_tmp[i])
	{
		if (str_tmp[i] == '=')
		{
			equal_notequal(env, str_tmp, i, str);
			break ;
		}
		else if(str_tmp[i] == 0)
		{
			equal_notequal(env, str_tmp, i, str);
			break ;
		}
		i++;
	}
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
			if (tmp->exp == 1 || tmp->exp == 2)
			{
				ft_printf_fd(1, "declare -x ");
				ft_printf_fd(1, "%s", tmp->env_name);
				if(tmp->exp == 1)
					ft_printf_fd(1, "=");
				ft_printf_fd(1, "%s", tmp->env_value);
				ft_printf_fd(1, "\n");
			}
			tmp = tmp->next_env;
		}
	}
	else
	{
		while(i < ac)
		{
			if(av[i][0] == '=')
			{
				ft_printf_fd(2, "Conchiglia: export: '=': not a valid identifier\n");
				i++;
			}
			ft_export_env(env, av[i++]);
		}
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
	env_matrix = malloc(sizeof(char *) * (len + 1));
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
	env_matrix[i] = 0;
	return (env_matrix);
}