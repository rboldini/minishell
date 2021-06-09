#include "../includes/minishell.h"

void	ft_new_history(t_history **curr)
{
	t_history *new;

	new = ft_calloc(1, sizeof(t_history));
	ft_memset(new, 0, sizeof(t_history));
	if ((*curr))
		(*curr)->next = new;
	new->row = malloc(0);
	new->next = NULL;
	new->index = 0;
	new->prev = *curr;
	*curr = new;
}

void	hook_line(t_shell *minishell)
{
	char	c;

	c = (char)ft_hook_char();
	free (minishell->current->row);
	minishell->current->row = ft_calloc(1024, sizeof(char));
	while (c != '\n')
	{
		if (ft_special_keys(c, minishell))
		{
			ft_fill_row(minishell->current, c);
			write(1, &c, 1);
		}
		c = (char)ft_hook_char();
	}
	if (minishell->n_up)
	{
		free (minishell->tmp->row);
		minishell->tmp->row = minishell->current->row;
		minishell->current->row = minishell->current->old;
		minishell->current->old = NULL;
		minishell->tmp->index = ft_strlen(minishell->tmp->row);
		minishell->current->index = ft_strlen(minishell->current->row);
		minishell->current = minishell->tmp;
		free_old(minishell->current);
	}
	minishell->n_up = 0;
	write(1, "\n", 1);
}
