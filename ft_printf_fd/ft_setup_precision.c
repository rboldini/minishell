/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setup_precision.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbuonvin <vbuonvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 16:58:17 by vbuonvin          #+#    #+#             */
/*   Updated: 2021/07/01 17:06:57 by vbuonvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	prec_minor_len(t_option *lista, char *temp, int i)
{
	lista->output_p = (char *)ft_calloc(sizeof(char), lista->precision + 1);
	if (!lista->output_p)
		return ;
	while (i < lista->precision)
	{
		lista->output_p[i] = temp[i];
		i++;
	}
}

void	ft_setup_precision(t_option *lista, int len, char *temp)
{
	int	i;

	i = 0;
	lista->output_p = NULL;
	if (lista->precision < len)
		prec_minor_len(lista, temp, i);
	else if (lista->precision >= len)
	{
		lista->output_p = (char *)ft_calloc(sizeof(char), len + 1);
		if (!lista->output_p)
			return ;
		while (i < len)
		{
			lista->output_p[i] = temp[i];
			i++;
		}
	}
}
