#include "../../includes/minishell.h"

int	d_redirect2(char **res, char *eof)
{
	char	*tmp;

	get_prompt();
	ft_bzero(g_shell->current->row, ft_strlen(g_shell->current->row));
	g_shell->current->index = 0;
	hook_line(g_shell);
	if (!ft_strcmp(g_shell->current->row, eof))
	{
		return (0);
	}
	if (g_shell->abort_dred)
		return (0);
	g_shell->current->row[ft_strlen(g_shell->current->row)] = '\n';
	tmp = ft_strjoin(*res, g_shell->current->row);
	free(*res);
	*res = tmp;
	return (1);
}

char	*d_redirect(char *eof)
{
	char	*res;

	res = malloc(sizeof(char));
	*res = 0;
	ft_new_history(&g_shell->current);
	set_prompt("peppere> ");
	g_shell->in_dred = 1;
	while (1)
	{
		if (!d_redirect2(&res, eof))
			break ;
	}
	if (!g_shell->abort_dred)
	{
		ft_bzero(g_shell->current->row, ft_strlen(g_shell->current->row));
		g_shell->current->index = 0;
	}
	return (res);
}
