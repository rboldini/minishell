/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_setup_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbuonvin <vbuonvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 10:25:48 by vbuonvin          #+#    #+#             */
/*   Updated: 2021/06/21 13:41:35 by rboldini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	setup_w_util(t_option *lista, int len, int i, int width)
{
	if (lista->negative && (lista->flag_minus || lista->flag_zero)
		&& (lista->type == 'd' || lista->type == 'i' || lista->type == 'u'
			|| lista->type == 'x' || lista->type == 'X'))
		len += 1;
	lista->output_w = (char *)ft_calloc(sizeof(char), (width - len + 1));
	if (!lista->output_w)
		return ;
	while (i < (width - len))
		lista->output_w[i++] = ' ';
	lista->output_w[i] = 0;
}

void	setup_z_util(t_option *lista, int nblen, int i, int zeroes)
{
	if (lista->negative && (!lista->width || lista->width < nblen))
		nblen -= 1;
	else if (lista->negative && lista->flag_zero && (lista->precision > -1))
		nblen -= 1;
	else if (lista->negative && lista->flag_minus
		&& !lista->flag_zero && zeroes > nblen && lista->precision == -1)
		nblen -= 1;
	else if (lista->negative && lista->flag_minus
		&& !lista->flag_zero && zeroes > nblen && lista->precision > -1)
		nblen -= 1;
	lista->output_zeroes
		= (char *)ft_calloc(sizeof(char), (zeroes - nblen) + 1);
	if (!lista->output_zeroes)
		return ;
	while (i < (zeroes - nblen))
		lista->output_zeroes[i++] = '0';
	lista->output_zeroes[i] = 0;
}
