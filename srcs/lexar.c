#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <stdio.h>

int 	ft_process_del(char c)
{
	if (c == 127)
	{
		printf("\b \b");
		fflush(stdout);
		return (0);
	}
	return (1);
}

void ft_fill_row(t_history *curr, char c)
{
	size_t len;
	char *tmp;

	len = 0;
	if (curr->row)
		len = ft_strlen(curr->row);
	if (len)
		tmp = ft_strdup(curr->row);
	free(curr->row);
	curr->row = malloc(sizeof(char) * len + 1);
	ft_strlcpy(curr->row, tmp, len);
	curr->row[len - 1] = c;
	curr->row[len] = '\0';
}

void ft_clipboard(t_shell *minishell)
{
	(void)minishell;
}

void lexar(t_shell *minishell)
{
	int i;

	i = 0;
	char c = (char)ft_hook_char();

	minishell->current = malloc(sizeof(t_history));
	minishell->current->row = malloc(0);
	while (c != '\n')
	{
		ft_fill_row(minishell->current, c);
		if (ft_process_del(c))
		{
			printf("%c", c);
			fflush(stdout);
		}
		c = (char)ft_hook_char();
	}
	printf("\n");
	//minishell->splitted = ft_split(line, ' ');
	//quotes(minishell);
	//return (line);
}
