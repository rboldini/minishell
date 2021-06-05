#include "../includes/minishell.h" //da rifare con nuovo sistema env

void ft_gotoroot(t_env *env)
{
	if(chdir("~") == -1)
	{
		ft_printf_fd(stderr, "Error: %s\n", strerror(errno));
		return ;
	}
	ft_edit_env(env, "OLDPWD", ft_getenv(env, "PWD"));
	ft_edit_env(env, "PWD", "~");
}

void ft_goback(t_env *env, char *curr_path)
{
	int errnum;
	int i;
	char *prev_path;
	int k;

	errnum = 0;
	k = 0;
	i = ft_strlen(curr_path);
	while(curr_path[i] != '/')
		i--;
	prev_path = malloc(sizeof(char) * i + 1);
	while(k < i)
	{
		prev_path[k] = curr_path[k];
		k++;
	}
	prev_path[k] = 0;
	if(chdir(prev_path) == -1)
	{
		errnum = errno;
		ft_printf_fd(stderr, "Error: %s\n", strerror(errnum));
		return ;
	}
	ft_edit_env(env, "OLDPWD", curr_path);
	ft_edit_env(env, "PWD", prev_path);
}

void ft_cd(int ac, char **av, t_env *env)
{
	char *curr_path;
	char *next_path;
	int errnum;
	char *error;
	int i;

	i = 0;
	errnum = 0;
	curr_path = ft_getenv(env, "PWD");
	if(!ft_strcmp(av[i], "."))
		ft_gotoroot(env);
	else if(!ft_strcmp(av[i], ".."))
		ft_goback(env, curr_path);
	else
	{
		next_path = ft_strjoin(curr_path, av[i]);
		if(chdir(next_path) == -1)
		{
			errnum = errno;
			ft_printf_fd(stderr, "Error: %s\n", strerror(errnum));
			return ;
		}
		ft_edit_env(env, "OLDPWD", curr_path);
		ft_edit_env(env, "PWD", next_path);
	}
}


