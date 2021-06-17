#include "../../includes/minishell.h"

void	ft_signal(int sig)
{
	if (sig == 2)
	{
		printf("hai premuto ctrl + C\t");
		fflush(stdout);
	}
	if (sig == 3)
	{
		printf("hai premuto ctrl + \\\t");
		fflush(stdout);
	}
}

void	ft_hook_signal(void)
{
	signal(2, ft_signal);
	signal(3, ft_signal);
}
