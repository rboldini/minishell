#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <stdio.h>

int 	ft_process_del(char c, t_shell *minishell)
{
	if (c == 127)
	{	
		if (minishell->current->index > (int)ft_strlen(minishell->prompt))
		{
			minishell->current->row[minishell->current->index - 1] = '\0';
			minishell->current->index--;
			printf("\b \b");
			fflush(stdout);
			return (0);
		}
	}
	return (1);
}

void	ft_fill_row(t_history *curr, char c)
{
	size_t	len;
	char	*tmp;

	len = 0;
	if ((*curr).row)
		len = ft_strlen(curr->row);
	if (len % 1023 == 0)
	{
		tmp = ft_strdup(curr->row);
		free(curr->row);
		curr->row = malloc(len + 1024 * sizeof(char));
		ft_strlcpy(curr->row, tmp, len);
		free(tmp);
	}
	curr->row[len] = c;
	//if(c != 127 && curr->index != 0)
	curr->index++;
	//printf("%d", curr->index);
}

void	ft_clipboard(t_shell *minishell)
{
	(void)minishell;
}

void	lexar(t_shell *minishell)
{
	int		i;
	char	c;

	i = 0;
	c = (char)ft_hook_char();
	minishell->current = malloc(sizeof(t_history));
	minishell->current->row = calloc(1024, sizeof(char));
	while (c != '\n')
	{
		ft_fill_row(minishell->current, c);
		if (ft_process_del(c, minishell))
		{
			printf("%c", c);
			fflush(stdout);
		}
		c = (char)ft_hook_char();
	}
	printf("\n");
	//minishell->splitted = ft_split(line, ' ');
	//quotes(minishell);
	//return (line);
}

int	ft_hook_char(void)
{
	struct termios	before;
	struct termios	after;
	char			c;
	int				ret;

	tcgetattr (0, &before);
	ft_memcpy(&after, &before, sizeof(struct termios));
	after.c_lflag &= ~(ICANON | ECHO);
	after.c_cc[VMIN] = 1;
	after.c_cc[VTIME] = 0;
	tcsetattr (0, TCSANOW, &after);
	ret = (int)read (0, &c, sizeof(char));
	tcsetattr (0, TCSANOW, &before);
	if (ret == -1)
		exit(1);
	return (c);
}