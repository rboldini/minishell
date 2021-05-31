#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <stdio.h>

void	quotes(t_shell *minishell)
{
	int		i;
	int		j;
	int		itmp;
	char	*tmp;

	i = 1;
	itmp = 0;
	while (minishell->splitted[i])
	{
		j = (int)ft_strlen(minishell->splitted[i]) - 1;
		if(minishell->splitted[i][0] == 34 && minishell->splitted[i][j] == 34)
		{
			tmp = malloc(sizeof(char) * j);
			j = -1;
			while(minishell->splitted[i][j++])
			{
				if(minishell->splitted[i][j] == 92 && minishell->splitted[i][j] == 'n')
				{
					tmp[itmp] = '\n';
					itmp++;
					continue ;
				}
				else if(minishell->splitted[i][j] == 34)
					continue ;
				else
				{
					tmp[itmp] = minishell->splitted[i][j];
					itmp++;
				}
			}
			free(minishell->splitted[i]);
			minishell->splitted[i] = tmp;
			printf("%s\n", tmp);
			tmp = NULL;
		}
		i++;
	}
}

char *lexar(t_shell *minishell)
{
	char	*line;

	if (get_next_line(STDIN_FILENO, &line) == 1)
		;
	minishell->splitted = ft_split(line, ' ');
	quotes(minishell);
	return (line);
}
