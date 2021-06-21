/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbuonvin <vbuonvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 18:35:33 by vbuonvin          #+#    #+#             */
/*   Updated: 2021/06/21 13:41:35 by rboldini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strappend(char **s1, char *s2)
{
	unsigned int	i_n[2];
	char			*res;

	i_n[0] = 0;
	while (*(*s1 + i_n[0]))
		i_n[0]++;
	i_n[1] = i_n[0];
	while (*(s2 + i_n[0] - i_n[1]))
		i_n[0]++;
	res = malloc(sizeof(char) * (i_n[0] + 1));
	if (!res)
		return (0);
	i_n[1] = 0;
	i_n[0] = 0;
	while (*(*s1 + i_n[0]))
	{
		res[i_n[0]] = *(*s1 + i_n[0]);
		i_n[0]++;
	}
	while (*(s2 + i_n[1]))
		res[i_n[0]++] = *(s2 + i_n[1]++);
	res[i_n[0]] = 0;
	free(*s1);
	*s1 = res;
	return (1);
}

int	shift_memory(char *str, int size, int offset)
{
	ft_memmove(&str[0], &str[offset], size - offset);
	ft_memset(&str[size - offset], 0, offset);
	return (1);
}

int	free_line(char **line)
{
	free(line);
	return (0);
}

int	flush_buffer(char *buf, char **line)
{
	int		n;
	char	*tmp;

	tmp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!tmp)
		return (free_line(line));
	*tmp = 0;
	n = 0;
	while (n < BUFFER_SIZE && buf[n] != 0 && buf[n] != '\n')
	{
		*(tmp + n) = buf[n];
		n++;
	}
	*(tmp + n) = 0;
	shift_memory(buf, BUFFER_SIZE, n);
	if (!(ft_strappend(line, tmp)))
	{
		free(tmp);
		free(line);
		return (0);
	}
	free(tmp);
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static char	buf[BUFFER_SIZE];
	int			res;

	if ((fd < 0 || !line || BUFFER_SIZE <= 0 || fd > MAX_OPEN))
		return (-1);
	*line = malloc(sizeof(char));
	if (!(*line))
		return (-1);
	**line = 0;
	res = 1;
	while (res >= 0)
	{
		if (!(flush_buffer(buf, line)))
			return (-1);
		if (buf[0] == '\n' && shift_memory(buf, BUFFER_SIZE, 1))
			return (1);
		if (res == 0)
			return (0);
		res = read(fd, buf, BUFFER_SIZE);
	}
	return (-1);
}
