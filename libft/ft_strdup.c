/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbuonvin <vbuonvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 17:27:06 by vbuonvin          #+#    #+#             */
/*   Updated: 2021/05/31 12:10:40 by rboldini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*new;

	new = (char *)malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (new == NULL)
		return (NULL);
	ft_strlcpy(new, s1, ft_strlen(s1) + 1);
	return (new);
}
