#include "../includes/minishell.h" //da rifare con nuovo sistema env

void ft_set_oldpath(char *curr_path)
{
	int errnum;
	int i;
	errnum = 0;
	if (chdir("..") == -1) 
	{
		errnum = errno;
		ft_printf_fd(stderr, "Error: %s\n", strerror(errnum));
		return ;
	}
	setenv("PATH", ("OLDPWD"), 1);
	i = ft_strlen(curr_path);
	while(curr_path[i] != '/')
		i--;
	curr_path[i] = 0;
	setenv("OLDPWD", curr_path, 1);
}

void ft_cd(int ac, char **av, int fd)
{
	char *curr_path;
	char *next_path;
	int errnum;
	char *error;
	int i;

	i = 0;
	errnum = 0;
	curr_path = ft_calloc(sizeof(char), 500);
	if(ft_strcmp(av[0], ".") != 0 && ft_strcmp(av[0], ".."))
	{
		next_path = ft_strjoin(curr_path, av[0]);
		free(curr_path);
		if (chdir(next_path) == -1) 
		{
			errnum = errno;
			ft_printf_fd(stderr, "%s: %s\n",av[i], strerror(errnum));
			return ;
		}
		setenv("OLDPWD", curr_path, 1);
		setenv("PATH", next_path, 1);
	}
	else if(!ft_strcmp(av[0], ".."))
		ft_set_oldpath(curr_path);
}
