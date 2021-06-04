#include "../includes/minishell.h"

# define PATH_MAX 4096

int ft_pwd(void)
{
	char cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX) != NULL)
	{
		ft_putendl_fd(cwd, 1);
	}
	else
	{
		perror("Error\n");
		return (1);
	}
	return (0);
}

// int main()
// {
// 	ft_pwd();
// 	return (0);
// }


//void	ft_pwd(t_shell *minishell)
//{
//	char *s;
//	s = malloc(sizeof(char) * 500);
//	if (!minishell->splitted[1])
//		printf("%s\n", getcwd(s, 500));
//	else
//		printf(CC_RED"invalid argument number\n"CC_RESET);
//	free(s);
//}
//
//void	ft_cd(t_shell *minishell)
//{
//	char *cwd;
//	int i;
//
//	cwd = ft_calloc(500, 1);
//	if (!minishell->splitted[1])
//	{
//		setenv("OLDPWD", getcwd(cwd, 500), 1);
//		chdir(getenv("HOME"));
//		setenv("PWD", getenv("HOME"), 1);
//	}
//	else
//	{
//		getcwd(cwd, 500);
//		i = chdir(minishell->splitted[1]);
//		if (!i)
//		{
//			setenv("OLDPWD", cwd, 1);
//			free(cwd);
//			cwd = ft_calloc(500, 1);
//			setenv("PWD", getcwd(cwd, 500), 1);
//		}
//		else
//			printf(CC_RED"Invalid path\n"CC_RESET);
//	}
//	printf(CC_UGRN"Debug OLDPWD: %s\n"CC_RESET, getenv("OLDPWD"));
//	printf(CC_UGRN"Debug PWD: %s\n"CC_RESET, getenv("PWD"));
//}
