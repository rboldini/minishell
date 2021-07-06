/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbuonvin <vbuonvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 11:06:45 by vbuonvin          #+#    #+#             */
/*   Updated: 2021/07/06 19:22:17 by vbuonvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include "../libft/libft.h"

typedef struct s_option
{
	int			flag_minus;
	int			flag_zero;
	int			width;
	int			dot;
	int			precision;
	int			negative;
	int			arg_i;
	char		type;
	char		*output_w;
	char		*output_p;
	char		*output_zeroes;
	int			return_value;
	int			h_neg;
	int			fd;
}				t_option;

void			ft_putchar(char c, t_option *lista);
void			ft_putstr(const char *str, t_option *lista);
int				handle_negative(t_option *lista, int nblen);
char			*ft_exa_converter(unsigned int n, char c);
char			*ft_unsigned_itoa(unsigned int n);
char			*ft_address_converter(size_t n);
void			setup_struct(t_option *lista);
void			ft_control_flag(const char *str, int i, t_option *lista);
void			ft_control_w(const char *str,
					int i, t_option *lista, va_list argptr);
void			ft_control_p(const char *str,
					int i, t_option *lista, va_list argptr);
void			ft_control_type(const char *str, int i, t_option *lista);
void			ft_controllo(const char *str,
					int i, t_option *lista, va_list argptr);
void			ft_setup_width(t_option *lista, int len);
void			setup_w_util(t_option *lista, int len, int i, int width);
void			ft_setup_zero(t_option *lista, int nblen);
void			setup_z_util(t_option *lista, int nblen, int i, int zeroes);
void			ft_setup_precision(t_option *lista, int len, char *temp);
void			ft_setup_type(va_list argptr, t_option *lista);
void			process_char(t_option *lista, va_list argptr);
void			process_string(t_option *lista, va_list argptr);
void			process_pointer(t_option *lista, va_list argptr);
void			process_signed_decimal(t_option *lista, va_list argptr);
int				set_negative_nb(t_option *lista, int nblen, int nb);
void			print_prec_no_min_no_z(t_option *lista, int nblen, char *temp);
void			print_prec_min_z(t_option *lista, int nblen, char *temp);
void			process_unsigned_decimal(t_option *lista, va_list argptr);
void			process_unsigned_hex(t_option *lista, va_list argptr);
void			process_percentage(t_option *lista);
int				ft_printf_fd(int fd, const char *str, ...);
void			ft_setup_precision(t_option *lista, int len, char *temp);

#endif
