/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scilla <scilla@student.42.fr>              +#+  +:+       +#+        */
/*   By: vbuonvin <vbuonvin@student.42.fr>        +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 16:00:47 by scilla            #+#    #+#             */
/*   Updated: 2021/07/09 16:01:06 by scilla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_print_env(t_env *env)
{
	while (env)
	{
		printf("%s", env->env_name);
		printf("=");
		printf("%s\n", env->env_value);
		env = env->next_env;
	}
}

int	only_spaces(char *str)
{
	while (*str)
	{
		if (*str != ' ')
			return (0);
		str++;
	}
	return (1);
}
