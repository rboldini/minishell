#include <stdio.h>
#include "../includes/minishell.h"

void	close_anim(int sig)
{
	g_shell->anim = sig;
}

void	ft_hook_anim(void)
{
	signal(2, close_anim);
	signal(3, close_anim);
}

void	ft_update_shlvl(t_env *env)
{
	char	*lvl;
	int		nb_lvl;
	char	*new_lvl;

	lvl = ft_getenv(env, "SHLVL");
	if (lvl)
	{
		nb_lvl = ft_atoi(lvl);
		nb_lvl++;
		new_lvl = ft_itoa(nb_lvl);
		edit_env(&env, "SHLVL", new_lvl);
	}
}

void	watermark(void)
{
	int	i;

	g_shell->anim = 0;
	write(1, "\r\033[2K", 5);
	while (!g_shell->anim)
	{
		i = 0;
		while (i < 9 && !g_shell->anim)
		{
			ft_hook_anim();
			asciimation(i);
			clean_sleep();
			i++;
		}
	}
}
