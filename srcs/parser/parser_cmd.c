/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scilla <scilla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 16:53:17 by scilla            #+#    #+#             */
/*   Updated: 2021/07/05 19:31:40 by scilla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	copy_tcmd(t_cmd ***cmd_arr, t_cmd ***tmp_cmd_arr, int arr_len)
{
	int	n;

	n = 0;
	while (n < arr_len)
	{
		(*tmp_cmd_arr)[n] = (*cmd_arr)[n];
		n++;
	}
	return (n);
}

t_cmd	**add_tcmd(t_cmd **cmd_arr, t_cmd *comm, t_cv *cv)
{
	t_cmd	**tmp_cmd_arr;
	int		arr_len;
	int		n;

	arr_len = 0;
	if (!cmd_arr)
	{
		cmd_arr = malloc(sizeof(t_cmd *));
		*cmd_arr = NULL;
	}
	while (cmd_arr[arr_len])
		arr_len++;
	arr_len++;
	tmp_cmd_arr = malloc(sizeof(t_cmd *) * (arr_len + 1));
	tmp_cmd_arr[arr_len] = NULL;
	n = copy_tcmd(&cmd_arr, &tmp_cmd_arr, arr_len);
	tmp_cmd_arr[n] = NULL;
	free(cmd_arr);
	cmd_arr = tmp_cmd_arr;
	init_cmd(comm);
	cmd_arr[arr_len - 1] = comm;
	cv->arr = malloc(sizeof(char *));
	cv->arr[0] = 0;
	cv->stage = 0;
	cv->isb = 0;
	return (cmd_arr);
}
