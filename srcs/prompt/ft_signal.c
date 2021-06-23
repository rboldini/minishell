#include "../../includes/minishell.h"

void	ft_signal(int sig)
{
	if (sig == 2)
	{
		if(!minishell->pid)
		{
			ft_bzero(minishell->current->row, ft_strlen(minishell->current->row));
			ft_strlcpy(minishell->current->row, minishell->current->old, ft_strlen(minishell->current->old) + 1);
			minishell->current->index = ft_strlen(minishell->current->row);
			write(1, "\n", 1);
			write(1, getprompt(minishell), ft_strlen(getprompt(minishell)));
			while (minishell->current->next)
				minishell->current = minishell->current->next;
			minishell->current->index = 0;
		}
		else
			write(1, "\n", 1);
	}
	if (sig == 3)
	{
		if (minishell->pid)
		{
			kill(minishell->pid, 3);
			write(1, "\b \b\b \b", 6);
			printf("ho quittato bella\n");
			minishell->pid = 0;
		}
		
	}
}

void	ft_hook_signal(void)
{
	signal(2, ft_signal);
	signal(3, ft_signal);
}

