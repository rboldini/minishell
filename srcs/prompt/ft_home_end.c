#include "../../includes/minishell.h"

void	ft_home_end(int c, t_shell *minishell)
{
	if (c == 72)
	{
		while (minishell->current->index > 0)
		{
			write(1, "\b", 1);
			minishell->current->index--;
		}
	}
	else
	{
		while (minishell->current->index
			< (int)ft_strlen(minishell->current->row))
		{
			write(1, "\033[C", 3);
			minishell->current->index++;
		}
	}
}
