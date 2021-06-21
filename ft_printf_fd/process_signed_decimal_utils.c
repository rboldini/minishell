/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_signed_decimal_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbuonvin <vbuonvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 11:01:29 by vbuonvin          #+#    #+#             */
/*   Updated: 2021/06/21 13:41:35 by rboldini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	set_negative_nb(t_option *lista, int nblen, int nb)
{
	if (nb < 0)
	{
		lista->negative = 1;
		if (lista->width || lista->precision > -1 || lista->flag_zero)
			nblen -= 1;
	}
	return (nblen);
}

void	print_prec_no_min_no_z(t_option *lista, int nblen, char *temp)
{
	ft_setup_zero(lista, nblen);
	if (lista->width)
	{
		ft_setup_width(lista, nblen);
		lista->h_neg = handle_negative(lista, nblen);
		ft_putstr(lista->output_w, lista);
		free(lista->output_w);
		ft_putstr(lista->output_zeroes, lista);
		free(lista->output_zeroes);
	}
	else
	{
		lista->h_neg = handle_negative(lista, nblen);
		ft_putstr(lista->output_zeroes, lista);
		free(lista->output_zeroes);
	}
	if (lista->h_neg)
		ft_putstr(temp + 1, lista);
	else
		ft_putstr(temp, lista);
}

void	print_prec_min_z(t_option *lista, int nblen, char *temp)
{
	ft_setup_zero(lista, nblen);
	ft_setup_width(lista, nblen);
	lista->h_neg = handle_negative(lista, nblen);
	ft_putstr(lista->output_zeroes, lista);
	free(lista->output_zeroes);
	if (lista->h_neg)
		ft_putstr(temp + 1, lista);
	else
		ft_putstr(temp, lista);
	ft_putstr(lista->output_w, lista);
	free((void *)lista->output_w);
}
