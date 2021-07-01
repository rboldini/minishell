/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_setups.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbuonvin <vbuonvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 10:22:44 by vbuonvin          #+#    #+#             */
/*   Updated: 2021/07/01 17:07:55 by rboldini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_controllo(const char *str, int i, t_option *lista, va_list argptr)
{
	ft_control_flag(str, i, lista);
	ft_control_w(str, i, lista, argptr);
	ft_control_p(str, i, lista, argptr);
	ft_control_type(str, i, lista);
}

void	ft_setup_width(t_option *lista, int len)
{
	int	i;
	int	width;

	width = lista->width;
	i = 0;
	lista->output_w = NULL;
	if (lista->precision > -1 && lista->precision <= len
		&& lista->type == 's')
		len = lista->precision;
	else if (lista->precision > -1 && lista->precision >= len
		&& (lista->type == 'i' || lista->type == 'd' || lista->type == 'u'
			|| lista->type == 'x' || lista->type == 'X'))
		len = lista->precision;
	if (width > len)
		setup_w_util(lista, len, i, width);
	else
	{
		lista->output_w = (char *)ft_calloc(sizeof(char), (len + 1));
		if (!lista->output_w)
			return ;
		lista->output_w[i] = 0;
	}
}

void	ft_setup_zero(t_option *lista, int nblen)
{
	int	i;
	int	zeroes;

	lista->output_zeroes = NULL;
	i = 0;
	zeroes = lista->width;
	if (lista->precision > -1)
		zeroes = lista->precision;
	if (zeroes >= nblen)
		setup_z_util(lista, nblen, i, zeroes);
	else
	{
		lista->output_zeroes = (char *)ft_calloc(sizeof(char), (nblen + 1));
		if (!lista->output_zeroes)
			return ;
		lista->output_zeroes[i] = 0;
	}
}

void	ft_setup_type(va_list argptr, t_option *lista)
{
	if (lista->type == 'c')
		process_char(lista, argptr);
	else if (lista->type == 's')
		process_string(lista, argptr);
	else if (lista->type == 'p')
		process_pointer(lista, argptr);
	else if (lista->type == 'i')
		process_signed_decimal(lista, argptr);
	else if (lista->type == 'd')
		process_signed_decimal(lista, argptr);
	else if (lista->type == 'u')
		process_unsigned_decimal(lista, argptr);
	else if (lista->type == 'x' || lista->type == 'X')
		process_unsigned_hex(lista, argptr);
	else if (lista->type == '%')
		process_percentage(lista);
}
