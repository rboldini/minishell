#include "../../includes/minishell.h"

void	ft_goback(t_env **env)
{
	char	*tmp;

	if (chdir(ft_getenv(*env, "OLDPWD")) == -1)
	{
		ft_error(errno, 0, 0);
	}
	else
	{
		tmp = ft_strdup(ft_getenv(*env, "PWD"));
		set_pwd_oldpwd(env);
		edit_env(env, "PWD", ft_getenv(*env, "OLDPWD"));
		edit_env(env, "OLDPWD", tmp);
		free(tmp);
	}
}

void	ft_gohome(t_env **env)
{
	if (chdir(ft_getenv(*env, "HOME")) == -1)
	{
		ft_error(errno, 0, 0);
	}
	else
	{
		set_pwd_oldpwd(env);
		edit_env(env, "OLDPWD", ft_getenv(*env, "PWD"));
		edit_env(env, "PWD", ft_getenv(*env, "HOME"));
	}
}

void	ft_goroot(t_env **env)
{
	if (chdir("/") == -1)
	{
		ft_error(errno, 0, 0);
	}
	else
	{
		set_pwd_oldpwd(env);
		edit_env(env, "OLDPWD", ft_getenv(*env, "PWD"));
		edit_env(env, "PWD", "/");
	}
}

void	ft_cd(int ac, char **av, t_env **env)
{
	char	*curr_path;
	int		len;

	curr_path = ft_getenv(*env, "PWD");
	if (ac < 2 || !ft_strcmp("~", av[1]))
		ft_gohome(env);
	else if (!ft_strcmp(av[1], ".."))
		ft_goup(env, curr_path);
	else if (!ft_strcmp(av[1], "-"))
		ft_goback(env);
	else if (!ft_strcmp(av[1], "/"))
		ft_goroot(env);
	else if (ft_strcmp(av[1], "."))
	{
		len = ft_strlen(ft_getenv(*env, "HOME"));
		if (!ft_strncmp(av[1], ft_getenv(*env, "HOME"), len))
			ft_absolute_path(env, av[1]);
		else
			ft_relative_path(env, av[1]);
	}
}
