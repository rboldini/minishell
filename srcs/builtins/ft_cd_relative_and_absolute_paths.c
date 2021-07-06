#include "../../includes/minishell.h"

void	set_pwd_oldpwd(t_env **env)
{
	set_env(env, "PWD");
	set_env(env, "OLDPWD");
}

void	ft_absolute_path(t_env **env, char *absolute_path)
{
	if (chdir(absolute_path) == -1)
	{
		ft_error(errno, 0, 0);
	}
	else
	{
		set_pwd_oldpwd(env);
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
		set_pwd_oldpwd(env);
		edit_env(env, "OLDPWD", curr_path);
		edit_env(env, "PWD", next_path);
	}
	free(temp_path);
	free(next_path);
}

void	go_in_dir(t_env **env, char *curr_path, char *prev_path)
{
	if (chdir(prev_path) == -1)
		ft_error(errno, 0, 0);
	else
	{
		set_pwd_oldpwd(env);
		edit_env(env, "OLDPWD", curr_path);
		edit_env(env, "PWD", prev_path);
	}
}

void	ft_goup(t_env **env, char *curr_path)
{
	int		i;
	char	*prev_path;
	int		k;

	k = 0;
	i = ft_strlen(curr_path);
	while (curr_path[i] != '/')
		i--;
	if (i == 0)
		i = 1;
	prev_path = malloc(sizeof(char) * i + 1);
	while (k < i)
	{
		prev_path[k] = curr_path[k];
		k++;
	}
	prev_path[k] = 0;
	go_in_dir(env, curr_path, prev_path);
	free(prev_path);
}
