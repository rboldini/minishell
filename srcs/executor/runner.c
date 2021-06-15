#include "../../includes/minishell.h"

void	ft_runner(t_env *env, int ac, char **av)
{
	char **envp;
	char **paths;
	t_env *tmp;

	envp = exported_env_matrix(env);
	tmp = ft_getenv(env, "PATH");
	paths = ft_split(tmp->env_value, ':');
	
}