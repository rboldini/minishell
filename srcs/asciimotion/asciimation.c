#include "../../includes/minishell.h"

void	ft_sleep(void)
{
	int	s;

	s = 0;
	while (s++ < INT_MAX / 6)
		;
}

void	clean_frame(void)
{
	int	x;

	x = 0;
	write(1, "\b \b", 3);
	while (x < 9)
	{
		write(1, "\r\033[2K", 5);
		write(1, "\033[A", 9);
		x++;
	}
}

void	clean_sleep(void)
{
	ft_sleep();
	clean_frame();
}

void	asciimation(void)
{
	frame0();
	clean_sleep();
	frame1();
	clean_sleep();
	frame2();
	clean_sleep();
	frame3();
	clean_sleep();
	frame4();
	clean_sleep();
	frame5();
	clean_sleep();
	frame6();
	clean_sleep();
	frame7();
	clean_sleep();
	frame8();
	clean_sleep();
}
