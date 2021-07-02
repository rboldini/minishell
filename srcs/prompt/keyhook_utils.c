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

void	free_history(t_history *curr)
{
	while (curr->prev)
	{
		free(curr->row);
		curr = curr->prev;
		free(curr->next);
	}
	free(curr->row);
	free(curr);
}

void	ft_new_history(t_history **curr)
{
	t_history	*new;

	new = ft_calloc(1, sizeof(t_history));
	ft_memset(new, 0, sizeof(t_history));
	if ((*curr))
		(*curr)->next = new;
	new->row = malloc(sizeof(char));
	*new->row = 0;
	new->next = NULL;
	new->index = 0;
	new->prev = *curr;
	*curr = new;
}

int	ft_hook_char(void)
{
	char			c;
	int				ret;
	struct termios	before;
	struct termios	after;

	tcgetattr (0, &before);
	ft_memcpy(&after, &before, sizeof(struct termios));
	after.c_lflag &= ~(ICANON | ECHO);
	after.c_cc[VMIN] = 1;
	after.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &after);
	ret = (int)read(0, &c, sizeof(char));
	if (ret == -1)
		exit(1);
	tcsetattr (0, TCSANOW, &before);
	return (c);
}

void	finalize_history(void)
{
	ft_bzero(g_shell->tmp->row, ft_strlen(g_shell->tmp->row));
	ft_strlcpy(g_shell->tmp->row, g_shell->current->row,
		ft_strlen(g_shell->current->row) + 1);
	ft_bzero(g_shell->current->row, ft_strlen(g_shell->current->row));
	ft_strlcpy(g_shell->current->row, g_shell->current->old,
		ft_strlen(g_shell->current->old) + 1);
	free (g_shell->current->old);
	g_shell->current->old = NULL;
	g_shell->tmp->index = (int)ft_strlen(g_shell->tmp->row);
	g_shell->current = g_shell->tmp;
	free_old(g_shell->current);
}
