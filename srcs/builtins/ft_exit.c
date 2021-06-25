#include "../../includes/minishell.h"

void	ft_exit(t_shell *minishell)
{
	ft_free_env(minishell->env);
	free_history(minishell->current);
	printf("exit\n");
	exit(0);
}
