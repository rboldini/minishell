#include "../../includes/minishell.h"

void	ft_echo(int ac, char **av)
{
	int	i;
	int	n_flag;
	
	n_flag = 0;
	i = 1;
	if(ac != 1)
	{
		if(ft_strcmp(av[i], "-n") == 0)
		{
			while (ft_strcmp(av[i], "-n") == 0)
			{
				i++;
				n_flag = 1;
			}
		}
		while (i < ac)
		{
			ft_printf_fd(1, "%s", av[i]);
			if(i < ac - 1)
				ft_printf_fd(1, " ");
			i++;
		}
	}
	if (!n_flag)
		ft_printf_fd(1, "\n");
}