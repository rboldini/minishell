#include "../../includes/minishell.h"

int	edit_or_create_env(t_env *env, char *str, char *str_tmp, int i)
{
	t_env	*same_element;

	if (!str_tmp[i])
	{
		printf("Conchiglia: %s: No such file or directory\n", str_tmp);
		errno = 127;
		free(str_tmp);
		return (-1);
	}
	str_tmp[i] = 0;
	same_element = check_existing_env(env, str_tmp);
	if (same_element != 0)
	{
		edit_env(&env, same_element->env_name, str_tmp + i + 1);
		unset_env(&env, same_element->env_name);
		free(str_tmp);
		return (0);
	}
	else
	{
		create_new_env(&env, str, 0);
		free(str_tmp);
		return (0);
	}
	return (1);
}

int	check_and_add(t_env *env, char *str)
{
	int		i;
	char	*str_tmp;

	i = 0;
	str_tmp = ft_strdup(str);
	while (1)
	{
		if (str_tmp[0] == '=')
		{
			printf("Conchiglia: env: invalid argument\n");
			errno = 1;
			free(str_tmp);
			return (-1);
		}
		if (str_tmp[i] == '=' || str_tmp[i] == 0)
		{
			if (!edit_or_create_env(env, str, str_tmp, i))
				return (0);
			else if (edit_or_create_env(env, str, str_tmp, i) == -1)
				return (-1);
		}
		i++;
	}
	free(str_tmp);
	return (0);
}

void	ft_print_env_list(t_env *tmp)
{
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

void	ft_env(t_env *env, int ac, char **av)
{
	t_env	*tmp;
	int		i;
	int		flag;

	i = 1;
	tmp = env;
	if (ac < 2)
		ft_print_env_list(tmp);
	else
	{
		while (i <= ac - 1)
			flag = check_and_add(env, av[i++]);
		if (flag == -1)
			return ;
		ft_env(env, 1, 0);
		i = 1;
		while (av[i])
		{
			printf("%s\n", av[i]);
			i++;
		}
	}
}
