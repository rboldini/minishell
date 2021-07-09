#include "../../includes/minishell.h"

char	*escape_dq(char	*str)
{
	char	*res;
	int		i;

	res = malloc(sizeof(char) * ft_strlen(str) * 2 + 3);
	res[0] = '"';
	i = 1;
	while (*str)
	{
		if (*str == '"')
		{
			res[i] = '\\';
			i++;
		}
		res[i] = *str;
		i++;
		str++;
	}
	res[i] = '"';
	res[i + 1] = 0;
	return (res);
}

void	print_exp_envs(t_env *tmp)
{
	char	*str_esc;

	while (tmp)
	{
		if (tmp->exp == 1 || tmp->exp == 2)
		{
			ft_printf_fd(1, "declare -x ");
			ft_printf_fd(1, "%s", tmp->env_name);
			if (tmp->exp == 1)
				ft_printf_fd(1, "=");
			str_esc = escape_dq(tmp->env_value);
			if (tmp->exp == 1)
				ft_printf_fd(1, "%s", str_esc);
			free(str_esc);
			ft_printf_fd(1, "\n");
		}
		tmp = tmp->next_env;
	}
}

void	ft_export(t_env *env, int ac, char **av)
{
	t_env	*tmp;
	int		i;

	i = 1;
	tmp = env;
	if (ac < 2)
		print_exp_envs(tmp);
	else
	{
		while (i < ac)
		{
			if (av[i][0] == '=')
			{
				ft_printf_fd(2, "Conchiglia: export: ");
				ft_printf_fd(2, "'=': not a valid identifier\n");
				g_shell->exit_code = 1;
				i++;
			}
			else
				ft_export_env(env, av[i++]);
		}
	}
}
