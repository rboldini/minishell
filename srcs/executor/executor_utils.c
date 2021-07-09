/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scilla <scilla@student.42.fr>              +#+  +:+       +#+        */
/*   By: vbuonvin <vbuonvin@student.42.fr>        +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 16:00:04 by scilla            #+#    #+#             */
/*   Updated: 2021/07/09 16:00:04 by scilla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*return_exec(char *tmp, char **av, char	**paths)
{
	char	*join;

	(void)tmp;
	if (ft_isdir(av[0]))
		return (ft_strdup(av[0]));
	else
	{
		join = elab_joined(av, paths);
		if (join != NULL)
			return (join);
		ft_error(errno, av[0], 1);
	}
	return (NULL);
}
