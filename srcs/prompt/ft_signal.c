#include "../../includes/minishell.h"

void	ctrl_c(void)
{
	ft_bzero(minishell->current->row, ft_strlen(minishell->current->row));
	ft_strlcpy(minishell->current->row, minishell->current->old,
		ft_strlen(minishell->current->old) + 1);
	minishell->current->index = ft_strlen(minishell->current->row);
	free_old(minishell->current);
	write(1, "\n", 1);
	write(1, "\r\033[2K", 5);
	set_prompt("\e[1;35mCONCHIGLIA -> % \e[0m");
	get_prompt();
	while (minishell->current->next)
		minishell->current = minishell->current->next;
	minishell->current->index = 0;
	if (minishell->in_dred)
		minishell->abort_dred = 1;
	minishell->abort = 1;
}

void	ft_signal(int sig)
{
	if (sig == 2)
	{
		if (!minishell->pid)
			ctrl_c();
		else
		{
			write(1, "\n", 1);
		}
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
