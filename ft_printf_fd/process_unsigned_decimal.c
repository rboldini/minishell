/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_unsigned_decimal.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbuonvin <vbuonvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 18:46:53 by vbuonvin          #+#    #+#             */
/*   Updated: 2021/06/21 13:41:35 by rboldini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	no_min_z(t_option *lista, char *temp, int nblen)
{
	if (lista->flag_zero)
	{
		if ((lista->precision > -1 && !lista->width)
			|| (lista->precision < 0 && lista->width))
		{
			ft_setup_zero(lista, nblen);
			ft_putstr(lista->output_zeroes, lista);
			free(lista->output_zeroes);
		}
		else if (lista->precision > -1 && lista->width)
		{
			ft_setup_zero(lista, nblen);
			ft_setup_width(lista, nblen);
			ft_putstr(lista->output_w, lista);
			free(lista->output_w);
			ft_putstr(lista->output_zeroes, lista);
			free(lista->output_zeroes);
		}
		ft_putstr(temp, lista);
	}
}

static void	no_min_no_z(t_option *lista, char *temp, int nblen)
{
	if (lista->precision > -1)
	{
		ft_setup_zero(lista, nblen);
		if (lista->width)
		{
			ft_setup_width(lista, nblen);
			ft_putstr(lista->output_w, lista);
			free(lista->output_w);
			ft_putstr(lista->output_zeroes, lista);
			free(lista->output_zeroes);
			ft_putstr(temp, lista);
		}
		else
		{
			ft_putstr(lista->output_zeroes, lista);
			free(lista->output_zeroes);
			ft_putstr(temp, lista);
		}
		return ;
	}
	ft_setup_width(lista, nblen);
	ft_putstr(lista->output_w, lista);
	free(lista->output_w);
	ft_putstr(temp, lista);
}

static void	min(t_option *lista, char *temp, int nblen)
{
	if (lista->precision > -1)
	{
		ft_setup_zero(lista, nblen);
		ft_setup_width(lista, nblen);
		ft_putstr(lista->output_zeroes, lista);
		free(lista->output_zeroes);
		ft_putstr(temp, lista);
		ft_putstr(lista->output_w, lista);
		free(lista->output_w);
	}
	else
	{
		if (lista->width)
		{
			ft_setup_width(lista, nblen);
			ft_putstr(temp, lista);
			ft_putstr(lista->output_w, lista);
			free(lista->output_w);
		}
		else
			ft_putstr(temp, lista);
	}
}

static void	elaborate(t_option *lista, char *temp, int nblen)
{
	if (!lista->flag_minus)
	{
		if (lista->flag_zero)
			no_min_z(lista, temp, nblen);
		else
			no_min_no_z(lista, temp, nblen);
	}
	else if (lista->flag_minus)
		min(lista, temp, nblen);
	if (temp != NULL && temp[0] != 0)
		free(temp);
	temp = NULL;
}

void	process_unsigned_decimal(t_option *lista, va_list argptr)
{
	int				nblen;
	char			*temp;
	unsigned int	nb;

	lista->negative = 0;
	nb = va_arg(argptr, unsigned int);
	temp = ft_unsigned_itoa(nb);
	nblen = ft_strlen(temp);
	if (lista->precision == 0 && nb == 0)
	{
		ft_bzero(temp, 1);
		free(temp);
		temp[0] = 0;
		nblen = 0;
	}
	elaborate(lista, temp, nblen);
}
