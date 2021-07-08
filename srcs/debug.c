#include "../includes/minishell.h"

void	ft_print_env(t_env *env)
{
	while (env)
	{
		printf("%s", env->env_name);
		printf("=");
		printf("%s\n", env->env_value);
		env = env->next_env;
	}
}

int	only_spaces(char *str)
{
	while (*str)
	{
		if (*str != ' ')
			return (0);
		str++;
	}
	return (1);
}

/*
	void	get_pos(int *y, int *x)
	{
		char			buf[30] = {0};
		int				ret;
		int				i;
		int				pow;
		char			ch;
		struct termios	term;
		struct termios	restore;

		*y = 0;
		*x = 0;
		tcgetattr(0, &term);
		tcgetattr(0, &restore);
		term.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(0, TCSANOW, &term);
		write(1, "\033[6n", 4);
		i = 0;
		ch = 0;
		while (ch != 'R')
		{
			ret = read(0, &ch, 1);
			if (!ret)
			{
				tcsetattr(0, TCSANOW, &restore);
				return ;
			}
			buf[i] = ch;
			i++;
		}
		if (i < 2)
		{
			tcsetattr(0, TCSANOW, &restore);
			return ;
		}
		i -= 2;
		pow = 1;
		while (buf[i] != ';')
		{
			*x = *x + (buf[i] - '0') * pow;
			pow *= 10;
		}
		i--;
		pow = 1;
		while (buf[i] != '[')
		{
			*y = *y + (buf[i] - '0') * pow;
			pow *= 10;
		}
		tcsetattr(0, TCSANOW, &restore);
	}
*/
