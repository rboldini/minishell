#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <stdio.h>

char *lexar(t_shell *minishell)
{
	char	*line;

	if (get_next_line(STDIN_FILENO, &line) == 1)
		;
	minishell->splitted = ft_split(line, ' ');
	return (line);
}