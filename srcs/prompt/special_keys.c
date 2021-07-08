#include "../../includes/minishell.h"

void	ft_arrow_lr(int x, t_history *curr)
{
	if (x == 68 && curr->index > 0)
	{
		write(1, "\b", 1);
		curr->index--;
	}
	else if (x == 67 && curr->index != (int)ft_strlen(curr->row))
	{
		write(1, "\033[C", 3);
		curr->index++;
	}
	else
		write(1, "\a", 1);
}

void	process_backspace2(t_history *curr, int i)
{
	write(1, "\b", 1);
	while (i < (int)ft_strlen(curr->row))
	{
		curr->row[i - 1] = curr->row[i];
		write(1, &curr->row[i - 1], 1);
		i++;
	}
	curr->row[ft_strlen(curr->row) - 1] = 0;
	write(1, " \b", 2);
	i = -1;
	while (++i <= (int)ft_strlen(curr->row) - curr->index)
		write(1, "\b", 1);
	curr->index--;
}

int	ft_process_backspace(t_history *curr)
{
	int	i;

	i = curr->index;
	if (i > 0 && i < (int)ft_strlen(curr->row))
	{
		process_backspace2(curr, i);
	}
	else if (i == (int)ft_strlen(curr->row) && i > 0)
	{
		curr->row[i - 1] = 0;
		write(1, "\b \b", 3);
		curr->index--;
	}
	else
		write(1, "\a", 1);
	return (1);
}

void	ctrl_u(void)
{
	ft_delete_multiline();
	write(1, "\r\033[2K", 5);
	ft_bzero(g_shell->current->row, ft_strlen(g_shell->current->row));
	get_prompt();
	g_shell->current->index = 0;
}
