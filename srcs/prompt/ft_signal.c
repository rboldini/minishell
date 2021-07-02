#include "../../includes/minishell.h"

void	ctrl_c(void)
{
	ft_bzero(g_shell->current->row, ft_strlen(g_shell->current->row));
	ft_strlcpy(g_shell->current->row, g_shell->current->old,
		ft_strlen(g_shell->current->old) + 1);
	g_shell->current->index = ft_strlen(g_shell->current->row);
	free_old(g_shell->current);
	write(1, "\n", 1);
	write(1, "\r\033[2K", 5);
	set_prompt("\e[1;35mCONCHIGLIA -> % \e[0m");
	get_prompt();
	while (g_shell->current->next)
		g_shell->current = g_shell->current->next;
	g_shell->current->index = 0;
	if (g_shell->in_dred)
		g_shell->abort_dred = 1;
	g_shell->abort = 1;
}

void	ft_signal(int sig)
{
	if (sig == 2)
	{
		if (!g_shell->pid)
			ctrl_c();
		else
		{
			write(1, "\n", 1);
		}
	}
	if (sig == 3)
	{
		if (g_shell->pid)
		{
			kill(g_shell->pid, 3);
			write(1, "\b \b\b \b", 6);
			printf("ho quittato bella\n");
			g_shell->pid = 0;
		}
	}
}

void	ft_hook_signal(void)
{
	signal(2, ft_signal);
	signal(3, ft_signal);
}
