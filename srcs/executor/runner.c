#include "../../includes/minishell.h"

int	ft_isdir(char *path)
{
	int res;
	char *tmp;
	int i;

	i = (int)ft_strlen(path);
	tmp = ft_strdup(path);
	while (i >= 0)
	{
		if (tmp[i] == '/')
		{
			tmp[i] = 0;
			break ;
		}
		i--;
	}
	res = open(tmp, O_DIRECTORY);
	free(tmp);
	if (res != -1)
	{
		close(res);
		return (1);
	}
	return (0);
}

int	ft_isfile(char *path)
{
	int res;

	res = open(path, 0);
	if (res != -1)
	{
		close(res);
		return (1);
	}
	return (0);
}

void	ft_runner(t_env *env, char **av, char *path)
{
	char	**envp;

	if (!av[0])
		return ;
	envp = exported_env_matrix(env);
	if(execve(path, av, envp) == -1)
		ft_error(errno, av[0], 0);
	free(envp);
}