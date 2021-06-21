/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_percentage.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbuonvin <vbuonvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 19:10:13 by vbuonvin          #+#    #+#             */
/*   Updated: 2021/06/21 13:41:35 by rboldini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	no_min_z(t_option *lista, char temp)
{
	if ((lista->precision > -1 && !lista->width)
		|| (lista->precision < 0 && lista->width))
	{
		ft_setup_zero(lista, 1);
		ft_putstr(lista->output_zeroes, lista);
		free(lista->output_zeroes);
	}
	else if (lista->precision > -1 && lista->width)
	{
		ft_setup_zero(lista, 1);
		ft_setup_width(lista, 1);
		ft_putstr(lista->output_w, lista);
		free(lista->output_w);
		ft_putstr(lista->output_zeroes, lista);
		free(lista->output_zeroes);
	}
	ft_putchar(temp, lista);
}

static void	no_min_no_z(t_option *lista, char temp)
{
	if (lista->precision > -1)
	{
		ft_setup_zero(lista, 1);
		if (lista->width)
		{
			ft_setup_width(lista, 1);
			ft_putstr(lista->output_w, lista);
			free(lista->output_w);
			ft_putstr(lista->output_zeroes, lista);
			free(lista->output_zeroes);
			ft_putchar(temp, lista);
		}
		else
		{
			ft_putstr(lista->output_zeroes, lista);
			free(lista->output_zeroes);
			ft_putchar(temp, lista);
		}
		return ;
	}
	ft_setup_width(lista, 1);
	ft_putstr(lista->output_w, lista);
	free(lista->output_w);
	ft_putchar(temp, lista);
}

static void	min(t_option *lista, char temp)
{
	if (lista->precision > -1)
	{
		ft_setup_zero(lista, 1);
		ft_setup_width(lista, 1);
		ft_putstr(lista->output_zeroes, lista);
		free(lista->output_zeroes);
		ft_putchar(temp, lista);
		ft_putstr(lista->output_w, lista);
		free(lista->output_w);
	}
	else
	{
		if (lista->width)
		{
			ft_setup_width(lista, 1);
			ft_putchar(temp, lista);
			ft_putstr(lista->output_w, lista);
			free(lista->output_w);
		}
		else
			ft_putchar(temp, lista);
	}
}

static void	elaborate(t_option *lista, char temp)
{
	if (!lista->flag_minus)
	{
		if (lista->flag_zero)
			no_min_z(lista, temp);
		else
			no_min_no_z(lista, temp);
	}
	else if (lista->flag_minus)
		min(lista, temp);
}

void	process_percentage(t_option *lista)
{
	char	temp;

	temp = '%';
	elaborate(lista, temp);
}
