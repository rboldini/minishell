/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scilla <scilla@student.42.fr>              +#+  +:+       +#+        */
/*   By: vbuonvin <vbuonvin@student.42.fr>        +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 15:59:19 by scilla            #+#    #+#             */
/*   Updated: 2021/07/09 15:59:19 by scilla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		matrix[i] = NULL;
		i++;
	}
	free(matrix);
	matrix = NULL;
}

void	ft_free_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		free(tmp->env_name);
		free(tmp->env_value);
		env = tmp;
		tmp = tmp->next_env;
		free(env);
	}
}

void	ft_addback_env(t_env **env, t_env *new_env)
{
	t_env	*tmp;

	tmp = *env;
	if (*env == NULL)
	{
		*env = new_env;
		(*env)->next_env = NULL;
	}
	while (tmp->next_env)
		tmp = tmp->next_env;
	tmp->next_env = new_env;
}

t_env	*create_env_node(char *tmp_raw, char *raw_env, int export, int i)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	new->env_name = ft_strdup(tmp_raw);
	if (ft_strlen(raw_env) > ft_strlen(tmp_raw))
		new->env_value = ft_strdup(tmp_raw + i + 1);
	else
	{
		new->env_value = malloc(sizeof(char));
		*new->env_value = 0;
	}
	new->exp = export;
	new->next_env = 0;
	return (new);
}

void	create_new_env(t_env **env, char *raw_env, int export)
{
	int		i;
	t_env	*new;
	char	*tmp_raw;
	t_env	*check;

	i = 0;
	tmp_raw = ft_strdup(raw_env);
	while (tmp_raw[i] != '=' && tmp_raw[i])
		i++;
	tmp_raw[i] = '\0';
	check = check_existing_env(*env, tmp_raw);
	if (!check)
	{
		new = create_env_node(tmp_raw, raw_env, export, i);
		ft_addback_env(env, new);
	}
	else
	{
		free(check->env_value);
		check->env_value = ft_strdup(raw_env + i + 1);
	}
	free(tmp_raw);
}
