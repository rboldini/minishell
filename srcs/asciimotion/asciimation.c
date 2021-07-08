#include "../../includes/minishell.h"

void	ft_sleep(int n)
{
	int	s;

	s = 0;
	while (s++ < INT_MAX / n)
		;
}

void	clean_frame(void)
{
	int	x;

	x = 0;
	while (x < 9)
	{
		write(1, "\r\033[2K", 5);
		write(1, "\033[A", 9);
		x++;
	}
}

void	clean_sleep(void)
{
	ft_sleep(6);
	clean_frame();
}

void	asciimation(int n)
{
	if (n == 0)
		frame0();
	else if (n == 1)
		frame1();
	else if (n == 2)
		frame2();
	else if (n == 3)
		frame3();
	else if (n == 4)
		frame4();
	else if (n == 5)
		frame5();
	else if (n == 6)
		frame6();
	else if (n == 7)
		frame7();
	else if (n == 8)
		frame8();
}
