#include "../includes/minishell.h"

void ft_echo(t_shell *minishell)
{
	int i = 1;
	int arg_n = 0;
	int j;

	if (minishell->splitted[1] && !ft_strcmp(minishell->splitted[1], "-n"))
	{
		arg_n = 1;
		i++;
	}
	while(minishell->splitted[i])
	{
		j = 0;
		while(minishell->splitted[i][j])
		{
			if(minishell->splitted[i][j] == 34 || minishell->splitted[i][j] == 39)
				j++;
			else
			{
				printf("%c", minishell->splitted[i][j]);
				j++;
			}
			fflush(stdout);
		}
		if (minishell->splitted[i])
			printf(" ");
		i++;
	}
	if (!arg_n)
		printf("\n");
	else
		write(1, "%\n", 2);
}