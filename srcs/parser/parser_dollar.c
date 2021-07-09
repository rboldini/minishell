/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scilla <scilla@student.42.fr>              +#+  +:+       +#+        */
/*   By: vbuonvin <vbuonvin@student.42.fr>        +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 16:58:19 by scilla            #+#    #+#             */
/*   Updated: 2021/07/09 16:00:21 by scilla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*elab_errno(int *i, char *dst, char *var_name)
{
	char	*var_value;
	char	*tmp;

	(*i)++;
	var_value = ft_itoa(g_shell->exit_code);
	if (var_value || 1)
	{
		tmp = ft_strjoin(dst, var_value);
		free(dst);
		dst = tmp;
		free(var_value);
	}
	free(var_name);
	(*i)++;
	return (dst);
}

char	*append_env(const char *src, int *i, char **var_name, char *dst)
{
	char	*var_value;
	char	c;
	char	*tmp;

	(*i)++;
	c = *(src + *i);
	while ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9') || c == '_')
	{
		*var_name = app_char(src, i, *var_name);
		c = *(src + *i);
	}
	var_value = ft_get_allowed_env(g_shell->env, *var_name);
	if (var_value)
	{
		tmp = ft_strjoin(dst, var_value);
		free(dst);
		dst = tmp;
	}
	return (dst);
}

char	*elab_dollar(const char *src, int *i, char *dst)
{
	char	c;
	char	*var_name;

	var_name = malloc(sizeof(char));
	var_name[0] = 0;
	c = *(src + *i + 1);
	if (c == '?')
		return (elab_errno(i, dst, var_name));
	if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_'))
		dst = app_char(src, i, dst);
	else
		dst = append_env(src, i, &var_name, dst);
	free(var_name);
	return (dst);
}
