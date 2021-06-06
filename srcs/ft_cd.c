#include "../includes/minishell.h" //da rifare con nuovo sistema env

void	ft_gotoroot(t_env *env)
{
	if (chdir("~") == -1)
	{
		ft_printf_fd(stderr, "Error: %s\n", strerror(errno));
		return ;
	}
	ft_edit_env(env, "OLDPWD", ft_getenv(env, "PWD"));
	ft_edit_env(env, "PWD", "~");
}

void	ft_goback(t_env *env, char *curr_path)
{
	int		errnum;
	int		i;
	char	*prev_path;
	int		k;

	errnum = 0;
	k = 0;
	i = ft_strlen(curr_path);
	while (curr_path[i] != '/')
		i--;
	prev_path = malloc(sizeof(char) * i + 1);
	while (k < i)
	{
		prev_path[k] = curr_path[k];
		k++;
	}
	prev_path[k] = 0;
	if (chdir(prev_path) == -1)
	{
		errnum = errno;
		ft_printf_fd(stderr, "Error: %s\n", strerror(errnum));
		return ;
	}
	ft_edit_env(env, "OLDPWD", curr_path);
	ft_edit_env(env, "PWD", prev_path);
}

void ft_absolute_path(t_env *env, char *absolute_path)
{
	if (chdir(absolute_path) == -1)
	{
		ft_printf_fd(stderr, "Error: %s\n", strerror(errno));
		return ;
	}
	ft_edit_env(env, "OLDPWD", ft_getenv(env, "PWD"));
	ft_edit_env(env, "PWD", absolute_path);
}

void	ft_relative_path(t_env *env, char *relative_path)
{
	char *next_path;
	char *curr_path;

	curr_path = curr_path = ft_getenv(env, "PWD");
	next_path = ft_strjoin(curr_path, relative_path);
	if (chdir(next_path) == -1)
	{
		ft_printf_fd(stderr, "Error: %s\n", strerror(errno));
		return ;
	}
	ft_edit_env(env, "OLDPWD", curr_path);
	ft_edit_env(env, "PWD", next_path);
}

void	ft_cd(int ac, char **av, t_env *env)
{
	char	*curr_path;
	int len;

	curr_path = ft_getenv(env, "PWD");
	if (!ft_strcmp(av[0], ".") || !av[0])
		ft_gotoroot(env);
	else if (!ft_strcmp(av[0], ".."))
		ft_goback(env, curr_path);
	else
	{
		len = ft_strlen(ft_getenv(env, "HOME"));
		if(!ft_strncmp(av[0], ft_getenv(env, "HOME"), len))
			ft_absolute_path(env, av[0]);
		else
			ft_relative_path(env, av[0]);
	}
}


