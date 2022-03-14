/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-der <dvan-der@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/31 08:20:37 by rcappend      #+#    #+#                 */
/*   Updated: 2022/03/03 13:35:36 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

static char	*find_var_in_env(char *text, char **env)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	if (ft_isdigit(text[0]) || ft_strchr("\'\"\\$,.:/[{]}+=-&*^%#@!~", \
		text[len]))
		return (NULL);
	while (text[len] && !ft_strchr("\'\"\\$ ,.:/[{]}+=-&*^%#@!~", \
		text[len]))
		len++;
	while (env[i])
	{
		if (!ft_strncmp(text, env[i], len))
		{
			if (env[i][len] == '=')
				return (env[i]);
		}
		i++;
	}
	return (NULL);
}

static char	*get_value(char *env)
{
	char	*value;
	int		i;

	i = 0;
	if (!env)
		return (NULL);
	while (env[i] != '=')
		i++;
	value = ft_strdup(env + i + 1);
	if (!value)
	{
		errno = ENOMEM;
		exit_error(errno, "get_value", NULL);
	}
	return (value);
}

static char	*get_var(t_token *token, char **env, int last_pid, long i)
{
	char	*env_location;
	char	*var;

	if (token->text[i] == '?')
	{
		var = ft_itoa(last_pid);
		if (!var)
		{
			errno = ENOMEM;
			exit_error(errno, "get_var", NULL);
		}
		return (var);
	}
	env_location = find_var_in_env(token->text + i, env);
	var = get_value(env_location);
	if (ft_strlen(var) == 0)
		return (NULL);
	return (var);
}

static char	*get_rest(t_token *token, long i)
{
	char	*rest;

	if (ft_isdigit(token->text[i]) || \
		ft_strchr("?\'\"\\$,.:/[{]}+=-&*^%#@!~", token->text[i]))
		rest = ft_substr(token->text, i + 1, token->len - i + 1);
	else
	{
		while (!ft_strchr("\'\"\\$ ,.:/[{]}+=-&*^%#@!~", token->text[i]))
			i++;
		rest = ft_substr(token->text, i, token->len - i);
	}
	if (!rest)
	{
		errno = ENOMEM;
		exit_error(errno, "get_rest", NULL);
	}
	return (rest);
}

static void	combine(t_token *token, char *start, char *var, char *rest)
{
	long	total_len;

	free(token->text);
	total_len = ft_strlen(start);
	total_len += ft_strlen(var);
	total_len += ft_strlen(rest);
	total_len++;
	token->text = ft_calloc(total_len, 1);
	if (!token->text)
	{
		errno = ENOMEM;
		exit_error(errno, "combine", NULL);
	}
	ft_strlcpy(token->text, start, total_len);
	if (var)
		ft_strlcat(token->text, var, total_len);
	ft_strlcat(token->text, rest, total_len);
	free(start);
	free(var);
	free(rest);
	token->len = total_len - 1;
}

int	expander(t_token *token, char **env, int last_pid, long i)
{
	char	*start;
	char	*var;
	char	*rest;

	i++;
	if (!token->text[i] || ft_strchr(" \'\"", token->text[i]))
		return (NO_EXPAND);
	start = ft_substr(token->text, 0, i - 1);
	if (!start)
	{
		errno = ENOMEM;
		exit_error(errno, "expander", NULL);
	}
	var = get_var(token, env, last_pid, i);
	rest = get_rest(token, i);
	combine(token, start, var, rest);
	return (EXPANDED);
}
