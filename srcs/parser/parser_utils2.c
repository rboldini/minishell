/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scilla <scilla@student.42.fr>              +#+  +:+       +#+        */
/*   By: vbuonvin <vbuonvin@student.42.fr>        +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 16:58:19 by scilla            #+#    #+#             */
/*   Updated: 2021/07/09 16:00:28 by scilla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	new_buff(t_cv *cv, const char *cmd, int *i)
{
	cv->buff = next_token(cmd, i, &cv->isb);
	if (!cv->stage && ft_strlen(cv->buff))
		cv->arr = append_to_arr(cv->buff, &cv->comm->len, cv->arr);
}

void	move_arr(t_cv *cv)
{
	cv->comm->arr = cv->arr;
	if (!g_shell->abort && (cv->stage || !cv->arr || !cv->arr[0]))
	{
		ft_error(errno, 0, 258);
		g_shell->abort = 1;
		return ;
	}
}

t_cv	*alloc_cv(int *i)
{
	t_cv	*cv;

	cv = ft_calloc(1, sizeof(t_cv));
	*i = 0;
	return (cv);
}

t_cmd	**get_res(t_cv *cv)
{
	t_cmd	**res;

	res = cv->cmd_arr;
	free(cv);
	return (res);
}

void	fill_cv(t_cv *cv)
{
	cv->arr = malloc(sizeof(char *));
	cv->arr[0] = 0;
	cv->stage = 0;
	cv->isb = 0;
}
