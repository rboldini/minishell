/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbuonvin <vbuonvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 10:54:10 by vbuonvin          #+#    #+#             */
/*   Updated: 2021/06/21 13:41:35 by rboldini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_nblen(int n)
{
	int	slen;

	slen = 1;
	if (n < 0)
	{
		n *= -1;
		slen++;
	}
	while (slen < 11)
	{
		if (ft_isdigit(n + '0'))
			break ;
		n = n / 10;
		slen++;
	}
	return (slen);
}

char	*ft_converter(int n, char *newstring, int slen)
{
	if (n < 0)
	{
		n *= -1;
		newstring[0] = '-';
	}
	newstring[slen] = '\0';
	slen--;
	while (slen >= (newstring[0] == '-' ? 1 : 0))
	{
		newstring[slen] = (n % 10) + 48;
		n = n / 10;
		slen--;
	}
	return (newstring);
}

char	*ft_itoa(int n)
{
	int		slen;
	char	*newstring;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	slen = ft_nblen(n);
	newstring = (char *)malloc(sizeof(char) * (slen + 1));
	if (newstring == NULL)
		return (NULL);
	return (ft_converter(n, newstring, slen));
}
