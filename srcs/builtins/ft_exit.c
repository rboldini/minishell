#include "../../includes/minishell.h"

void	ft_exit(t_shell *g_shell)
{
	if (!ft_strcmp(g_shell->prompt, "peppere> "))
		ctrl_c();
	else
	{
		ft_free_env(g_shell->env);
		free_history(g_shell->current);
		printf("exit\n");
		exit(0);
	}
}
