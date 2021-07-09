/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scilla <scilla@student.42.fr>              +#+  +:+       +#+        */
/*   By: vbuonvin <vbuonvin@student.42.fr>        +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 16:01:19 by scilla            #+#    #+#             */
/*   Updated: 2021/07/09 16:01:20 by scilla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../includes/minishell.h"

void	close_anim(int sig)
{
	g_shell->anim = sig;
}

void	ft_hook_anim(void)
{
	signal(2, close_anim);
	signal(3, close_anim);
}

void	watermark(void)
{
	int	i;

	g_shell->anim = 0;
	write(1, "\r\033[2K", 5);
	while (!g_shell->anim)
	{
		i = 0;
		while (i < 9 && !g_shell->anim)
		{
			ft_hook_anim();
			asciimation(i);
			clean_sleep();
			i++;
		}
	}
}
