/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fminardi <fminardi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 16:53:17 by scilla            #+#    #+#             */
/*   Updated: 2021/07/05 13:46:38 by fminardi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	elab_pipe(t_cv *cv, int *i)
{
	cv->tmp_comm = malloc(sizeof(t_cmd));
	cv->comm->next = cv->tmp_comm;
	cv->comm->arr = cv->arr;
	cv->tmp_comm->next = 0;
	cv->comm = cv->comm->next;
	init_cmd(cv->comm);
	cv->comm->has_previous = 1;
	(*i)++;
	cv->arr = malloc(sizeof(char *));
	*cv->arr = NULL;
	cv->stage = 0;
	free(cv->buff);
	return (1);
}

void	check_stage2(t_cv *cv)
{
	if (cv->stage == 7 && ft_strlen(cv->buff))
	{
		free(cv->comm->eof);
		cv->comm->eof = cv->buff;
		cv->comm->has_dred = 1;
		cv->stage = 0;
	}
	else
		free(cv->buff);
}

void	check_stage(t_cv *cv)
{
	if ((cv->stage == 3 || cv->stage == 4) && ft_strlen(cv->buff))
	{
		if (cv->comm->file_out != 1)
			close(cv->comm->file_out);
		if (cv->stage == 3)
			cv->comm->file_out = open(cv->buff, O_CREAT | O_RDWR | O_TRUNC,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		else
		{
			cv->comm->file_out = open(cv->buff, O_CREAT | O_RDWR | O_APPEND,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			cv->comm->is_append = 1;
		}
		cv->stage = 0;
	}
	else if (cv->stage == 5 && ft_strlen(cv->buff))
	{
		if (cv->comm->file_in != 0)
			close(cv->comm->file_in);
		cv->comm->file_in = open(cv->buff, O_RDONLY);
		cv->stage = 0;
	}
	check_stage2(cv);
}

int	check_isb(t_cv *cv, const char *cmd, int *i)
{
	if (cv->isb == 7)
		cv->comm->has_dred = 1;
	if (cv->isb > 2)
		cv->stage = cv->isb;
	if (cv->isb == 4 || cv->isb == 7)
		(*i)++;
	if (*(cmd + *i) != 0)
		(*i)++;
	if (cv->isb == 6)
	{
		cv->stage = 0;
		return (1);
	}
	return (0);
}

t_cmd	**start_parsing(const char *cmd)
{
	t_cv	*cv;
	t_cmd	**res;
	int		i;

	cv = ft_calloc(1, sizeof(t_cv));
	i = 0;
	while (*(cmd + i) || !i)
	{
		cv->comm = malloc(sizeof(t_cmd));
		cv->cmd_arr = add_tcmd(cv->cmd_arr, cv->comm, cv);
		while (*(cmd + i))
		{
			cv->buff = next_token(cmd, &i, &cv->isb);
			if (!cv->stage && ft_strlen(cv->buff))
				cv->arr = append_to_arr(cv->buff, &cv->comm->len, cv->arr);
			if (cv->isb == 2 && elab_pipe(cv, &i))
				continue ;
			check_stage(cv);
			if (check_isb(cv, cmd, &i))
				break ;
		}
		cv->comm->arr = cv->arr;
	}
	res = cv->cmd_arr;
	free(cv);
	return (res);
}
