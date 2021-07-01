/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scilla <scilla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 17:48:40 by scilla            #+#    #+#             */
/*   Updated: 2021/07/01 17:49:13 by scilla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
