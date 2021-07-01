#include "../../includes/minishell.h"

void	ft_arrow_down(void)
{
	if (minishell->current->next)
	{
		minishell->n_up--;
		write(1, "\r\033[2K", 5);
		write(1, minishell->prompt, ft_strlen(minishell->prompt));
		minishell->current->index = ft_strlen(minishell->current->row);
		minishell->current = minishell->current->next;
		minishell->current->index = ft_strlen(minishell->current->row);
		write(1, minishell->current->row,
			  ft_strlen(minishell->current->row));
	}
	else if (minishell->tmp && ft_strlen(minishell->tmp->row))
	{
		minishell->current = minishell->tmp;
		write(1, "\r\033[2K", 5);
		write(1, minishell->prompt, ft_strlen(minishell->prompt));
		write(1, minishell->current->row,
			  minishell->current->index);
	}
}

void	ft_arrow_up(void)
{
	if (minishell->n_up == 0)
		minishell->tmp = minishell->current;
	minishell->current->index = ft_strlen(minishell->current->row);
	minishell->current = minishell->current->prev;
	minishell->current->index = ft_strlen(minishell->current->row);
	write(1, "\r\033[2K", 5);
	get_prompt();
	if (!minishell->current->old)
		minishell->current->old = ft_strdup(minishell->current->row);
	write(1, minishell->current->row,
		  ft_strlen(minishell->current->row));
	minishell->n_up++;
}

void	ft_arrow_ud(int x, t_shell *minishell)
{
	if (x == 65)
	{
		if (minishell->current->prev)
			ft_arrow_up();
	}
	else
		ft_arrow_down();
}

void	ft_process_delete(t_history *curr)
{
	int	i;
	int	len;

	i = curr->index;
	len = (int)ft_strlen(curr->row);
	if (curr->index != len)
	{
		while (i < (int)ft_strlen(curr->row))
		{
			curr->row[i] = curr->row[i + 1];
			write(1, &curr->row[i], 1);
			i++;
		}
		curr->row[i] = 0;
		write(1, " ", 1);
		i = 0;
		while (i < len - curr->index)
		{
			write(1, "\b", 1);
			i++;
		}
	}
	else
		write(1, "\a", 1);
}
