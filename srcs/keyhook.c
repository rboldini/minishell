#include "../includes/minishell.h"

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

int	ft_check_special_keys(void)
{
	int x;

	x = ft_hook_char();
	if (x == 27)
	{
		x = ft_hook_char();
		if (x == 91)
		{
			x = ft_hook_char();
			if (x == 65)
			else if (x == 66)
			else if (x == 67)
			else if (x == 68)
			else if (x == 51)
			else
				return (x);
		}
		return (x)
	}
	return (x);
}
void	hook_line(t_shell *minishell)
{
	char	c;

	c = (char)ft_hook_char();
	minishell->current = malloc(sizeof(t_history));
	minishell->current->row = calloc(1024, sizeof(char));
	while (c != '\n')
	{
		printf("%i\n", (int)c);
//		ft_fill_row(minishell->current, c);
//		ft_check_special_keys();
//		if (ft_process_del(c, minishell)) //TODO: check for -> escape char (int)27	,	arrow  (int) up > 27,91,65; down > 27,91,66; right > 27,91,67; left > 27,91,68; delete = 27,91,51,126
//		{
//			printf("%c", c);
//			fflush(stdout);
//		}
		c = (char)ft_hook_char();
	}
	//TODO: create a new instance of t_history
	printf("\n");
}
