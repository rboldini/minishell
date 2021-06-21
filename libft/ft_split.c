/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbuonvin <vbuonvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 17:56:59 by vbuonvin          #+#    #+#             */
/*   Updated: 2021/06/21 13:41:35 by rboldini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_word(const char *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
			count++;
			while (s[i] != '\0' && s[i] != c)
				i++;
		}
	}
	return (count);
}

static char	**cpyandstore(const char *s, char c, char **splitted, size_t wordnb)
{
	size_t	i;
	size_t	k;
	size_t	len;

	i = 0;
	k = 0;
	while (i < wordnb)
	{
		if (s[k] != c)
		{
			len = k;
			while (s[len] && s[len] != c)
				len++;
			splitted[i] = (char *)malloc(sizeof(char) * (len - k + 1));
			if (splitted[i] == NULL)
				return (NULL);
			ft_strlcpy(splitted[i], &s[k], (len - k + 1));
			i++;
			k = len;
		}
		else
			k++;
	}
	return (splitted);
}

char	**ft_split(const char *s, char c)
{
	char	**splitted;
	size_t	wordnb;

	if (!s)
		return (NULL);
	wordnb = ft_count_word(s, c);
	splitted = (char **)malloc(sizeof(char *) * (wordnb + 1));
	if (!(splitted))
		return (NULL);
	splitted[wordnb] = NULL;
	return (cpyandstore(s, c, splitted, wordnb));
}
