#include "../../includes/minishell.h"

void	ft_delete_multiline(void)
{
	int	i;

	i = 0;
	while (ft_strlen(g_shell->current->row)
		&& i < (int)(ft_strlen(g_shell->current->row)
		+ ft_strlen(g_shell->prompt)))
	{
		write(1, "\b \b", 3);
		i++;
	}
}

void	ft_arrow_down(void)
{
	if (g_shell->current->next)
	{
		g_shell->n_up--;
		ft_delete_multiline();
		write(1, "\r\033[2K", 5);
		write(1, g_shell->prompt, ft_strlen(g_shell->prompt));
		g_shell->current->index = ft_strlen(g_shell->current->row);
		g_shell->current = g_shell->current->next;
		g_shell->current->index = ft_strlen(g_shell->current->row);
		write(1, g_shell->current->row,
			  ft_strlen(g_shell->current->row));
	}
	else if (g_shell->tmp && ft_strlen(g_shell->tmp->row))
	{
		ft_delete_multiline();
		g_shell->current = g_shell->tmp;
		write(1, g_shell->prompt, ft_strlen(g_shell->prompt));
		write(1, g_shell->current->row,
			  g_shell->current->index);
	}
}

void	ft_arrow_up(void)
{
	int	i;

	i = 0;
	while (ft_strlen(g_shell->current->row)
		   && i < (int)(ft_strlen(g_shell->current->row)))
	{
		write(1, "\b \b", 3);
		i++;
	}
	write(1, "\r\033[2K", 5);
	get_prompt();
	if (g_shell->n_up == 0)
		g_shell->tmp = g_shell->current;
	g_shell->current->index = ft_strlen(g_shell->current->row);
	g_shell->current = g_shell->current->prev;
	g_shell->current->index = ft_strlen(g_shell->current->row);
	if (!g_shell->current->old)
		g_shell->current->old = ft_strdup(g_shell->current->row);
	write(1, g_shell->current->row,
		  ft_strlen(g_shell->current->row));
	g_shell->n_up++;
}

void	ft_arrow_ud(int x, t_shell *g_shell)
{
	if (x == 65)
	{
		if (g_shell->current->prev)
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
