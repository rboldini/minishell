/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scilla <scilla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 16:58:19 by scilla            #+#    #+#             */
/*   Updated: 2021/07/06 17:10:43 by scilla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**append_to_arr(const char *str, int *len, char **arr)
{
	char	**tmp;
	int		i;

	tmp = malloc(sizeof(char *) * (*len + 2));
	i = 0;
	while (i < *len)
	{
		tmp[i] = arr[i];
		i++;
	}
	tmp[i] = ft_strdup(str);
	tmp[i + 1] = 0;
	free(arr);
	(*len)++;
	return (tmp);
}

char	*app_char(const char *cmd, int *i, char *buff)
{
	char	*cc;
	char	*tmp;

	cc = malloc(sizeof(char) * 2);
	cc[0] = *(cmd + *i);
	cc[1] = 0;
	tmp = ft_strjoin(buff, cc);
	free(cc);
	free(buff);
	(*i)++;
	return (tmp);
}

char	*escape_slash(const char *src, int *i, char *dst)
{
	char	c;
	int		k;

	k = 0;
	c = *(src + *i + 1);
	if (c == '\\' || c == '"' || c == '\'' || c == '?')
	{
		dst = app_char(&c, &k, dst);
		(*i)++;
		(*i)++;
	}
	else
	{
		dst = app_char(src, i, dst);
	}
	return (dst);
}

t_cv	*set_cv(t_cv *cv)
{
	free(cv->comm);
	cv->comm = malloc(sizeof(t_cmd));
	cv->cmd_arr = add_tcmd(cv->cmd_arr, cv->comm, cv);
	return (cv);
}
