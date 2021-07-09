/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scilla <scilla@student.42.fr>              +#+  +:+       +#+        */
/*   By: vbuonvin <vbuonvin@student.42.fr>        +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 16:00:02 by scilla            #+#    #+#             */
/*   Updated: 2021/07/09 16:00:03 by scilla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_error(int errnum, char *str, int cmd_flag)
{
	if (cmd_flag == 258)
	{
		g_shell->abort = 1;
		ft_printf_fd(2, "Conchiglia: syntax error\n");
		g_shell->exit_code = 258;
	}
	else if (cmd_flag == 139)
	{
		g_shell->abort = 1;
		ft_printf_fd(2, "Segmentation fault: 11\n");
		g_shell->exit_code = 139;
	}
	else if (cmd_flag > 0)
	{
		ft_printf_fd(2, "Conchiglia: %s: command not found\n", str);
		g_shell->exit_code = 127;
		g_shell->abort = 1;
	}
	else if (str)
		ft_printf_fd(2, "Conchiglia: %s: %s\n", str, strerror(errnum));
	else
		ft_printf_fd(2, "Conchiglia: %s\n", strerror(errnum));
	return ;
}
