#include "../../includes/minishell.h"

int	ft_isfile(char *path)
{
	int res;
	char *tmp;
	int i;

	i = ft_strlen(path);
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
	printf("dir: %s\n", tmp);
	res = open(tmp, O_DIRECTORY);
	printf("%i\n", res);
	if (res != -1)
	{
		close(res);
		return (1);
	}
	return (0);
}

void	ft_runner(t_env *env, int ac, char **av)
{
	char **envp;
	char **paths;
	char *tmp;

	(void)ac;
	envp = exported_env_matrix(env);
	tmp = ft_getenv(env, "PATH");
	paths = ft_split(tmp, ':');
	if (ft_isfile(av[0]))
	{
		execve(av[0], av, envp);
	}
	else
	{

	}
}