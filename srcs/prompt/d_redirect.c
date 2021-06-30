#include "../../includes/minishell.h"

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
		if (!ft_strcmp(minishell->current->row, eof))
			break ;
		if (minishell->abort)
			break ;
		minishell->current->row[ft_strlen(minishell->current->row)] = '\n';
		tmp = ft_strjoin(res, minishell->current->row);
		free(res);
		res = tmp;
	}
	ft_bzero(minishell->current->row, ft_strlen(minishell->current->row));
	minishell->current->index = 0;
	return (res);
}
