#include "../../includes/minishell.h"

void	ft_absolute_path(t_env **env, char *absolute_path)
{
	if (chdir(absolute_path) == -1)
	{
		ft_error(errno, 0, 0);
	}
	else
	{
		set_env(env, "PWD");
		set_env(env, "OLDPWD");
		edit_env(env, "OLDPWD", ft_getenv(*env, "PWD"));
		edit_env(env, "PWD", absolute_path);
	}
}

void	ft_relative_path(t_env **env, char *relative_path)
{
	char	*next_path;
	char	*curr_path;
	char	*temp_path;

	curr_path = ft_getenv(*env, "PWD");
	if (!ft_strcmp(curr_path, "/"))
		curr_path[0] = 0;
	temp_path = ft_strjoin(curr_path, "/");
	next_path = ft_strjoin(temp_path, relative_path);
	if (chdir(next_path) == -1)
	{
		ft_error(errno, 0, 0);
	}
	else
	{
		set_env(env, "PWD");
		set_env(env, "OLDPWD");
		edit_env(env, "OLDPWD", curr_path);
		edit_env(env, "PWD", next_path);
	}
	free(temp_path);
	free(next_path);
}
