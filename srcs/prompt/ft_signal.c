#include "../../includes/minishell.h"

void	ft_signal(int sig)
{
	if (sig == 2)
	{

	}
	if (sig == 3)
	{

	}
}

void	ft_hook_signal(void)
{
	signal(2, ft_signal);
	signal(3, ft_signal);
}
