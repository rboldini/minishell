#include "../includes/minishell.h"

int	env_lst_size(t_env *env)
{
	t_env *tmp;
	int res;

	res = 0;
	while(tmp)
	{
		res++;
		tmp = tmp->next_env;
	}
	return (res);
}

void ft_export_env(t_env *env, char *str)
{
	t_env *tmp;
	int i;
	char *str_tmp;

	i = 0;
	tmp = env;
	str_tmp = ft_strdup(tmp);
	while(str_tmp[i])
	{
		if(str_tmp[i] == '=' || str_tmp[i] == 0)
		{
			str_tmp[i] = 0;
			while(tmp)
			{
				if(ft_strcmp(str, tmp->env_name) == 0)
				{
					edit_env(env, str + 1, 1);
					free(str_tmp);
					return ;
				}
				tmp = tmp->next_env;
			}
		}
		i++;
	}
	create_new_env(env, str, 1);
	free(str_tmp);
}

void ft_export(t_env *env)
{
	t_env *tmp;
	
	tmp = env;
	while(tmp)
	{
		if(tmp->exp == 1)
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

char **exported_env_matrix(t_env *env)
{
	int len;
	char **env_matrix;

	len = env_lst_size(env);
	env_matrix = malloc(sizeof(char *) * len);
	while() // da finire copia della lista in matrice da inviare a processi figli VAR=arg
	
}