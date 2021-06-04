#include "../includes/minishell.h"

void ft_echo(int ac, char **av, int fd)
{
	int i;
	
	i = 0;
	while(i < ac)
	{
		ft_printf_df(fd, "%s", av[i]);
		i++;
	}
	if(ft_strcmp(av[0], "-n") == 0)
		ft_printf_fd(fd, "\n");
}