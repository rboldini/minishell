/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_negative.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbuonvin <vbuonvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 10:41:04 by vbuonvin          #+#    #+#             */
/*   Updated: 2021/06/21 13:41:35 by rboldini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	neg_no_min(t_option *lista, int nblen, int i)
{
	if (lista->output_w != NULL && lista->width >= nblen && !lista->flag_zero)
	{
		while (lista->output_w[i] != '\0')
			i++;
		if (i)
			i -= 1;
		lista->output_w[i] = '-';
		return (1);
	}
	if ((lista->precision >= nblen && lista->width < nblen)
		|| (lista->output_zeroes != NULL))
		lista->output_zeroes[0] = '-';
	return (1);
}

int	handle_negative(t_option *lista, int nblen)
{
	int	i;

	i = 0;
	if (lista->negative && !lista->flag_minus)
		return (neg_no_min(lista, nblen, i));
	if (lista->negative && lista->flag_minus)
	{
		if ((lista->precision > nblen && lista->width < nblen)
			|| (lista->output_zeroes != NULL))
		{
			lista->output_zeroes[0] = '-';
			return (1);
		}
	}
	return (0);
}
