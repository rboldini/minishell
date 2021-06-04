#include "../includes/minishell.h"

void	ft_process_delete()
{

}

void	ft_arrow_ud()
{

}

void	ft_arrow_lr()
{

}

int 	ft_process_backspace(char c, t_shell *minishell)
{
	if (c == 127)
	{
		if (minishell->current->index > (int)ft_strlen(minishell->prompt))
		{
			minishell->current->row[minishell->current->index - 1] = '\0';
			minishell->current->index--;
			printf("\b \b");
			fflush(stdout);
			return (0);
		}
	}
	return (1);
}
