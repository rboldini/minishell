/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scilla <scilla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 16:53:17 by scilla            #+#    #+#             */
/*   Updated: 2021/07/01 17:57:32 by scilla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	next_char(char *str, char c, int start)
{
	while (*(str + start))
	{
		if (*(str + start) == c)
			return (start);
		start++;
	}
	return (-1);
}

int	is_break(const char *cmd, int i)
{
	char	c;

	c = *(cmd + i);
	if (c == ' ' || c == 0)
		return (1);
	if (c == '>' && *(cmd + i + 1) == '>')
		return (4);
	if (c == '<' && *(cmd + i + 1) == '<')
		return (7);
	if (c == '>')
		return (3);
	if (c == '<')
		return (5);
	if (c == '|')
		return (2);
	if (c == ';')
		return (6);
	return (0);
}

char	*next_token(const char *cmd, int *i, int *isb)
{
	char	*buff;

	buff = malloc(sizeof(char));
	buff[0] = 0;
	while (1)
	{
		*isb = is_break(cmd, *i);
		if (*isb)
			break ;
		if (*(cmd + *i) == '\'')
			buff = elab_quote(cmd, i, buff);
		else if (*(cmd + *i) == '"')
			buff = elab_dquote(cmd, i, buff);
		else if (*(cmd + *i) == '$')
			buff = elab_dollar(cmd, i, buff);
		else if (*(cmd + *i) == '\\' && *i < (int)ft_strlen(cmd) - 1)
			buff = escape_slash(cmd, i, buff);
		else
			buff = app_char(cmd, i, buff);
	}
	return (buff);
}

void	init_cmd(t_cmd *comm)
{
	comm->file_in = 0;
	comm->file_out = 1;
	comm->err_out = 2;
	comm->is_append = 0;
	comm->len = 0;
	comm->next = NULL;
	comm->has_previous = 0;
	comm->eof = malloc(sizeof(char));
	*comm->eof = 0;
	comm->has_dred = 0;
}
