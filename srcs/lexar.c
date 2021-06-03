#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <stdio.h>

int 	ft_process_del(char c, t_shell *minishell)
{
	size_t len;

	if (c == 127)
	{
		len = ft_strlen(minishell->current->row);
		if (len > 0)
		{
			minishell->current->row[len - 1] = '\0';
			printf("\b \b");
			fflush(stdout);
			return (0);
		}
	}
	return (1);
}

void ft_fill_row(t_history *curr, char c)
{
	size_t len;
	char *tmp;

	len = 0;
	if ((*curr).row)
		len = ft_strlen(curr->row);
	if (len % 1023 == 0)
	{
		tmp = ft_strdup(curr->row);
		free(curr->row);
		curr->row = malloc(sizeof(char) * len + 1024);
		len += 1024;
		ft_strlcpy(curr->row, tmp, len);
	}
	ft_strlcpy(curr->row, tmp, len);
	curr->row[len] = c;
	curr->row[len + 1] = '\0';
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
	minishell->current->row = calloc(1024, sizeof(char));
	while (c != '\n')
	{
		ft_fill_row(minishell->current, c);
		if (ft_process_del(c, minishell))
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
