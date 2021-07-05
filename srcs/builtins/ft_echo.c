#include "../../includes/minishell.h"

int	analyse_flag(char **av)
{
	int	i;
	int	k;
	int	flag;

	flag = 1;
	k = 0;
	i = 1;
	while (av[i])
	{
		k = 0;
		if (av[i][k] == '-')
		{
			k++;
			if (av[i][k] == '-')
				return (flag);
			while (av[i][k] == 'n' || av[i][k] == '-')
			{
				if (av[i][k] == '-')
					return (flag);
				k++;
			}
		}
		else
			return (flag);
		flag += 1;
		i++;
	}
	return (flag);
}

void	ft_echo(int ac, char **av)
{
	int	i;
	int	n_flag;

	n_flag = 0;
	i = 1;
	if (ac != 1)
	{
		n_flag = analyse_flag(av);
		i = n_flag;
		while (i < ac)
		{
			ft_printf_fd(1, "%s", av[i]);
			if (i < ac - 1)
				ft_printf_fd(1, " ");
			i++;
		}
	}
	if (n_flag < 2)
		ft_printf_fd(1, "\n");
}
