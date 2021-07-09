/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scilla <scilla@student.42.fr>              +#+  +:+       +#+        */
/*   By: vbuonvin <vbuonvin@student.42.fr>        +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 15:59:58 by scilla            #+#    #+#             */
/*   Updated: 2021/07/09 15:59:59 by scilla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd(void)
{
	char	*test;

	test = malloc(sizeof(char) * 4096);
	test = getcwd(test, 4096);
	ft_printf_fd(1, "%s\n", test);
	free(test);
}
