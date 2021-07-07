#include "../../includes/minishell.h"

char	*return_exec(char *tmp, char **av, char	**paths)
{
	char	*join;

	paths = ft_split(tmp, ':');
	if (ft_isdir(av[0]))
	{
		ft_free_matrix(paths);
		return (ft_strdup(av[0]));
	}
	else
	{
		join = elab_joined(av, paths);
		ft_free_matrix(paths);
		if (join != NULL)
			return (join);
		ft_error(errno, av[0], 1);
	}
	return (NULL);
}
