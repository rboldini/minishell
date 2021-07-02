#include "../../includes/minishell.h"

void	print_exp_envs(t_env *tmp)
{
	while (tmp)
	{
		if (tmp->exp == 1 || tmp->exp == 2)
		{
			ft_printf_fd(1, "declare -x ");
			ft_printf_fd(1, "%s", tmp->env_name);
			if (tmp->exp == 1)
				ft_printf_fd(1, "=");
			ft_printf_fd(1, "%s", tmp->env_value);
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
				i++;
			}
			else
				ft_export_env(env, av[i++]);
		}
	}
}
