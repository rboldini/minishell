/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scilla <scilla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 16:53:17 by scilla            #+#    #+#             */
/*   Updated: 2021/07/01 17:14:50 by scilla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	*elab_quote(const char *src, int *i, char *dst)
{
	(*i)++;
	while (*(src + *i))
	{
		if (*(src + *i) == '\'')
		{
			(*i)++;
			break ;
		}
		dst = app_char(src, i, dst);
	}
	return (dst);
}

char	*elab_dquote(const char *src, int *i, char *dst)
{
	(*i)++;
	while (*(src + *i))
	{
		if (*(src + *i) == '"')
		{
			(*i)++;
			break ;
		}
		else if (*(src + *i) == '$')
			dst = elab_dollar(src, i, dst);
		else
			dst = app_char(src, i, dst);
	}
	return (dst);
}

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
}

t_cmd	**start_parsing(const char *cmd)
{
	t_cmd	**cmd_arr;
	t_cmd	**tmp_cmd_arr;
	t_cmd	*comm;
	t_cmd	*tmp_comm;
	char	**arr;
	int		i;
	int		n;
	char	*buff;
	int		stage;
	int		isb;
	int		arr_len;

	cmd_arr = malloc(sizeof(t_cmd*));
	cmd_arr[0] = NULL;
	i = 0;
	arr_len = 0;
	while (1)
	{
		arr_len++;
		tmp_cmd_arr = malloc(sizeof(t_cmd*) * (arr_len + 1));
		tmp_cmd_arr[arr_len] = NULL;
		n = 0;
		while (n < arr_len)
		{
			tmp_cmd_arr[n] = cmd_arr[n];
			n++;
		}
		free(cmd_arr);
		cmd_arr = tmp_cmd_arr;
		comm = malloc(sizeof(t_cmd));
		cmd_arr[arr_len - 1] = comm;
		init_cmd(comm);
		arr = malloc(0);
		comm->eof = malloc(sizeof(char));
		*comm->eof = 0;
		comm->has_dred = 0;
		stage = 0;
		isb = 0;
		while (*(cmd + i))
		{
			buff = next_token(cmd, &i, &isb);
			if (!stage && ft_strlen(buff))
				arr = append_to_arr(buff, &comm->len, arr);
			if (isb == 2)
			{
				tmp_comm = malloc(sizeof(t_cmd));
				comm->next = tmp_comm;
				comm->arr = arr;
				tmp_comm->next = 0;
				comm = comm->next;
				comm->eof = malloc(sizeof(char));
				*comm->eof = 0;
				comm->has_dred = 0;
				init_cmd(comm);
				comm->has_previous = 1;
				i++;
				arr = malloc(sizeof(char*));
				*arr = NULL;
				stage = 0;
				free(buff);
				continue ;
			}
			if (stage == 3 && ft_strlen(buff))
			{
				if (comm->file_out != 1)
					close(comm->file_out);
				comm->file_out = open(buff, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
				stage = 0;
			}
			if (stage == 4 && ft_strlen(buff))
			{
				if (comm->file_out != 1)
					close(comm->file_out);
				comm->file_out = open(buff, O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
				comm->is_append = 1;
				stage = 0;
			}
			if (stage == 5 && ft_strlen(buff))
			{
				if (comm->file_in != 0)
					close(comm->file_in);
				comm->file_in = open(buff, O_RDONLY);
				stage = 0;
			}
			if (isb == 7)
				comm->has_dred = 1;
			if (stage == 7 && ft_strlen(buff))
			{
				free(comm->eof);
				comm->eof = buff;
				comm->has_dred = 1;
				stage = 0;
			}
			else
				free(buff);
			if (isb > 2)
				stage = isb;
			if (isb >= 2 && isb != 7)
				comm->has_dred = 0;
			if (isb == 4 || isb == 7)
				i++;
			if (*(cmd + i) != 0)
				i++;
			if (isb == 6)
			{
				stage = 0;
				break ;
			}
		}
		comm->arr = arr;
		if (!*(cmd + i))
			break ;
	}
	return (cmd_arr);
}
