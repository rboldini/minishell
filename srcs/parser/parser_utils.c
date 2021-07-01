#include "../../includes/minishell.h"

char	**append_to_arr(const char *str, int *len, char **arr)
{
	char	**tmp;
	int		i;

	tmp = malloc(sizeof(char *) * (*len + 2));
	i = 0;
	while (i < *len)
	{
		tmp[i] = arr[i];
		i++;
	}
	// remove system strdup
	tmp[i] = ft_strdup(str);
	tmp[i + 1] = 0;
	free(arr);
	(*len)++;
	return (tmp);
}

char	*app_char(const char *cmd, int *i, char *buff)
{
	char	*cc;
	char	*tmp;

	cc = malloc(sizeof(char) * 2);
	cc[0] = *(cmd + *i);
	cc[1] = 0;
	tmp = ft_strjoin(buff, cc);
	free(cc);
	free(buff);
	(*i)++;
	return (tmp);
}

char	*escape_slash(const char *src, int *i, char *dst)
{
	char	c;
	int		k;

	k = 0;
	c = *(src + *i + 1);
	if (c == '\\' || c == '"' || c == '\'' || c == '?')
	{
		dst = app_char(&c, &k, dst);
		(*i)++;
		(*i)++;
	}
	else
	{
		dst = app_char(src, i, dst);
	}
	return (dst);
}

typedef struct s_dollar
{
	char	c;
	char	*var_name;
	char	*var_value;
	char	*tmp;
}			t_dollar;

char	*elab_dollar(const char *src, int *i, char *dst)
{
	char	c;
	char	*var_name;
	char	*var_value;
	char	*tmp;

	var_name = malloc(sizeof(char));
	var_name[0] = 0;
	c = *(src + *i + 1);
	if (c == '?')
	{
		(*i)++;
		var_value = ft_itoa(errno);
		if (var_value)
		{
			tmp = ft_strjoin(dst, var_value);
			free(dst);
			dst = tmp;
		}
		free(var_name);
		(*i)++;
		return (dst);
	}
	if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_'))
	{
		dst = app_char(src, i, dst);
	}
	else
	{
		(*i)++;
		c = *(src + *i);
		while ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
			|| (c >= '0' && c <= '9') || c == '_')
		{
			var_name = app_char(src, i, var_name);
			c = *(src + *i);
		}
		var_value = ft_getenv(minishell->env, var_name);
		if (var_value)
		{
			tmp = ft_strjoin(dst, var_value);
			free(dst);
			dst = tmp;
		}
	}
	free(var_name);
	return (dst);
}
