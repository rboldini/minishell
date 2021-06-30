#include "../../includes/minishell.h"

char	*d_redirect(char *eof)
{
	char *res;
	char *tmp;

	res = malloc(sizeof(char));
	*res = 0;
	ft_new_history(&minishell->current);
	set_prompt("peppere> ");
	minishell->in_dred = 1;
	while (1)
	{
		get_prompt();
		ft_bzero(minishell->current->row, ft_strlen(minishell->current->row));
		minishell->current->index = 0;
		hook_line(minishell);
		if (!ft_strcmp(minishell->current->row, eof))
			break ;
		if (minishell->abort_dred)
		{
			break ;
		}
		minishell->current->row[ft_strlen(minishell->current->row)] = '\n';
		tmp = ft_strjoin(res, minishell->current->row);
		free(res);
		res = tmp;
	}
	if (!minishell->abort_dred)
	{
		ft_bzero(minishell->current->row, ft_strlen(minishell->current->row));
		minishell->current->index = 0;
	}
	return (res);
}
