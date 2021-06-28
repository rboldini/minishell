#include "../../includes/minishell.h"
/*
t_shell *copy_shell()
{
	t_shell		*copy;
	t_history	*indice;
	t_history 	*tmp;
	t_history	*tmp_curr;

	indice = minishell->current;
	copy->prompt = NULL;
	copy->current = NULL;
	tmp = NULL;
	while (indice)
	{
		copy->current = malloc(sizeof(t_history));
		copy->current->next = NULL;
		copy->current->prev = tmp;
		if (tmp)
			copy->current->prev->next = copy->current;
		tmp = copy->current;
		copy->current->old = ft_strdup(indice->old);
		copy->current->row = ft_strdup(indice->row);
		copy->current->index = indice->index;
		indice = indice->next;
	}
	copy->tmp = NULL;
	copy->n_up = 0;
	copy->pid = 0;
	copy->env = NULL;
	return (copy);
}
*/

char	*d_redirect(char *eof)
{
	char *res;
	char *tmp;

	res = malloc(sizeof(char));
	*res = 0;
	ft_new_history(&minishell->current);
	set_prompt("peppere> ");
	while (1)
	{
		get_prompt();
		ft_bzero(minishell->current->row, ft_strlen(minishell->current->row));
		minishell->current->index = 0;
		hook_line(minishell);
		printf("HL: %s\n", minishell->current->row);
		if (!ft_strcmp(minishell->current->row, eof))
		{

			break ;
		}
		minishell->current->row[ft_strlen(minishell->current->row)] = '\n';
		tmp = ft_strjoin(res, minishell->current->row);
		free(res);
		res = tmp;
	}
	ft_bzero(minishell->current->row, ft_strlen(minishell->current->row));
	minishell->current->index = 0;
	return (res);
}
