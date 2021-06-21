/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_signed_decimal.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbuonvin <vbuonvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 17:41:49 by vbuonvin          #+#    #+#             */
/*   Updated: 2021/06/21 13:41:35 by rboldini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	no_min_z(t_option *lista, int nblen, char *temp)
{
	if ((lista->precision > -1 && !lista->width)
		|| (lista->precision < 0 && lista->width))
	{
		ft_setup_zero(lista, nblen);
		lista->h_neg = handle_negative(lista, nblen);
		ft_putstr(lista->output_zeroes, lista);
		free(lista->output_zeroes);
	}
	else if (lista->precision > -1 && lista->width)
	{
		ft_setup_zero(lista, nblen);
		ft_setup_width(lista, nblen);
		lista->h_neg = handle_negative(lista, nblen);
		ft_putstr(lista->output_w, lista);
		free(lista->output_w);
		ft_putstr(lista->output_zeroes, lista);
		free(lista->output_zeroes);
	}
	if (lista->h_neg)
		ft_putstr(temp + 1, lista);
	else
		ft_putstr(temp, lista);
}

static void	no_min_no_z(t_option *lista, int nblen, char *temp)
{
	if (lista->precision > -1)
		print_prec_no_min_no_z(lista, nblen, temp);
	else
	{
		ft_setup_width(lista, nblen);
		lista->h_neg = handle_negative(lista, nblen);
		ft_putstr(lista->output_w, lista);
		free(lista->output_w);
		if (lista->h_neg && lista->width >= nblen)
			ft_putstr(temp + 1, lista);
		else
			ft_putstr(temp, lista);
	}
}

static void	dec_min_z(t_option *lista, int nblen, char *temp)
{
	if (lista->precision > -1)
		print_prec_min_z(lista, nblen, temp);
	else
	{
		if (lista->width)
		{
			ft_setup_width(lista, nblen);
			lista->h_neg = handle_negative(lista, nblen);
			if (lista->h_neg && lista->width > nblen)
				ft_putstr(temp + 1, lista);
			else
				ft_putstr(temp, lista);
			ft_putstr(lista->output_w, lista);
			free(lista->output_w);
		}
		else
		{
			if (lista->h_neg)
				ft_putstr(temp + 1, lista);
			else
				ft_putstr(temp, lista);
		}
	}
}

static void	elaborate(t_option *lista, int nblen, char *temp, int nb)
{
	if (!lista->flag_minus)
	{
		nblen = set_negative_nb(lista, nblen, nb);
		if (lista->flag_zero)
			no_min_z(lista, nblen, temp);
		else
			no_min_no_z(lista, nblen, temp);
	}
	else if (lista->flag_minus)
	{
		nblen = set_negative_nb(lista, nblen, nb);
		dec_min_z(lista, nblen, temp);
	}
	if (temp != NULL && temp[0] != 0)
		free(temp);
	temp = NULL;
}

void	process_signed_decimal(t_option *lista, va_list argptr)
{
	int		nblen;
	char	*temp;
	int		nb;

	temp = NULL;
	nb = va_arg(argptr, int);
	temp = ft_itoa(nb);
	nblen = ft_strlen(temp);
	if (lista->precision == 0 && nb == 0)
	{
		ft_bzero(temp, 1);
		free(temp);
		temp[0] = 0;
		nblen = 0;
	}
	elaborate(lista, nblen, temp, nb);
}
