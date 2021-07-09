/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scilla <scilla@student.42.fr>              +#+  +:+       +#+        */
/*   By: vbuonvin <vbuonvin@student.42.fr>        +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 15:59:29 by scilla            #+#    #+#             */
/*   Updated: 2021/07/09 15:59:29 by scilla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	loop_flag(int i, int k, char **av, int flag)
{
	while (av[i])
	{
		k = 0;
		if (av[i][k] == '-')
		{
			k++;
			if (av[i][k] == '-')
				return (flag);
			while (av[i][k] == 'n' || av[i][k] == '-')
			{
				if (av[i][k] == '-')
					return (flag);
				k++;
			}
		}
		else
			return (flag);
		flag += 1;
		i++;
	}
	return (flag);
}

int	analyse_flag(char **av)
{
	int	i;
	int	k;
	int	flag;

	flag = 1;
	k = 0;
	i = 1;
	flag = loop_flag(i, k, av, flag);
	return (flag);
}

void	ft_echo(int ac, char **av)
{
	int	i;
	int	n_flag;

	n_flag = 0;
	i = 1;
	if (ac != 1)
	{
		n_flag = analyse_flag(av);
		i = n_flag;
		while (i < ac)
		{
			ft_printf_fd(1, "%s", av[i]);
			if (i < ac - 1)
				ft_printf_fd(1, " ");
			i++;
		}
	}
	if (n_flag < 2)
		ft_printf_fd(1, "\n");
	g_shell->exit_code = 0;
}
