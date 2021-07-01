#include "../../includes/minishell.h"

void	free_old(t_history *curr)
{
	while (curr->prev)
	{
		free (curr->old);
		curr->old = NULL;
		curr = curr->prev;
	}
	free (curr->old);
	curr->old = NULL;
}

void	ft_arrow_ud(int x, t_shell *minishell)
{
	if (x == 65)
	{
		if (minishell->current->prev)
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
	}
	else
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
}

void	ft_arrow_lr(int x, t_history *curr)
{
	if (x == 68 && curr->index > 0)
	{
		write(1, "\b", 1);
		curr->index--;
	}
	else if(x == 67 && curr->index != (int)ft_strlen(curr->row))
	{
		write(1, "\033[C", 3);
		curr->index++;
	}
	else
		write(1, "\a", 1);
}

int 	ft_process_backspace(t_history *curr)
{
	int	i;

	i = curr->index;
	if (i > 0 && i < (int)ft_strlen(curr->row))
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
