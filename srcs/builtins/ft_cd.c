#include "../../includes/minishell.h"

void ft_goback(t_env **env)
{
	char *tmp;

	if (chdir(ft_getenv(*env, "OLDPWD")) == -1)
	{
		ft_printf_fd(2, "Error: %s\n", strerror(errno));
		return ;
	}
	tmp = ft_strdup(ft_getenv(*env, "PWD"));
	//free(ft_getenv(*env, "PWD"));
	edit_env(env, "PWD", ft_getenv(*env, "OLDPWD"));
	edit_env(env, "OLDPWD", tmp);
}

void	ft_gohome(t_env **env)
{
	if (chdir(ft_getenv(*env, "HOME")) == -1)
	{
		ft_printf_fd(2, "Error: %s\n", strerror(errno));
		return ;
	}
	edit_env(env, "OLDPWD", ft_getenv(*env, "PWD"));
	edit_env(env, "PWD", ft_getenv(*env, "HOME"));
}

void	ft_goup(t_env **env, char *curr_path)
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
	if(i == 0)
		i = 1;
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
		ft_printf_fd(2, "Error: %s\n", strerror(errnum));
		return ;
	}
	edit_env(env, "OLDPWD", curr_path);
	edit_env(env, "PWD", prev_path);
}

void ft_absolute_path(t_env **env, char *absolute_path)
{
	if (chdir(absolute_path) == -1)
	{
		ft_printf_fd(2, "%s: %s\n", absolute_path, strerror(errno));
		return ;
	}
	edit_env(env, "OLDPWD", ft_getenv(*env, "PWD"));
	edit_env(env, "PWD", absolute_path);
}

void	ft_relative_path(t_env **env, char *relative_path)
{
	char *next_path;
	char *curr_path;

	curr_path = ft_getenv(*env, "PWD");
	if(!ft_strcmp(curr_path, "/"))
		curr_path[0] = 0;
	next_path = ft_strjoin(curr_path, "/");
	next_path = ft_strjoin(next_path, relative_path);
	if (chdir(next_path) == -1)
	{
		ft_printf_fd(2, "Error: %s\n", strerror(errno));
		return ;
	}
	edit_env(env, "OLDPWD", curr_path);
	edit_env(env, "PWD", next_path);
}

void ft_goroot(t_env **env)
{
	if (chdir("/") == -1)
	{
		ft_printf_fd(2, "%s: %s\n", "/", strerror(errno));
		return ;
	}
	edit_env(env, "OLDPWD", ft_getenv(*env, "PWD"));
	edit_env(env, "PWD", "/");
}

void	ft_cd(int ac, char **av, t_env **env)
{
	char	*curr_path;
	int		len;

	curr_path = ft_getenv(*env, "PWD");
	if(ac < 2 || !ft_strcmp("~", av[1])) //broken
		ft_gohome(env);
	else if (!ft_strcmp(av[1], "..")) //working
		ft_goup(env, curr_path);
	else if(!ft_strcmp(av[1], "-")) //broken
		ft_goback(env);
	else if(!ft_strcmp(av[1], "/")) //to_do
		ft_goroot(env);
	else if(ft_strcmp(av[1], ".")) //working - relative and absolute
	{
		len = ft_strlen(ft_getenv(*env, "HOME"));
		if(!ft_strncmp(av[1], ft_getenv(*env, "HOME"), len))
			ft_absolute_path(env, av[1]);
		else
			ft_relative_path(env, av[1]);
	}
}


