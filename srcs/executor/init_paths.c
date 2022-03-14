/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_paths.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-der <dvan-der@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/08 09:26:10 by rcappend      #+#    #+#                 */
/*   Updated: 2022/03/07 13:13:13 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <executor.h>

int	init_heredoc(t_cmd *cmd)
{
	t_red	*i;

	while (cmd)
	{
		i = cmd->input;
		while (i)
		{
			if (i->type == HERE_DOC)
			{
				i->heredoc = here_doc(i->file_name);
				if (i->heredoc == -1)
					return (EXIT_FAILURE);
			}
			i = i->next;
		}
		cmd = cmd->next;
	}
	return (EXIT_SUCCESS);
}

char	*find_in_env(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			return (env[i]);
		i++;
	}
	return (NULL);
}

char	**init_paths(char **env)
{
	char	**path;
	char	*temp;
	int		i;

	i = 0;
	temp = find_in_env(env);
	if (!temp)
		path = ft_split("", ':');
	else
		path = ft_split(temp + 5, ':');
	ft_check_malloc(path, "make_path_env");
	i = 0;
	while (path[i])
	{
		temp = ft_strjoin(path[i], "/");
		ft_check_malloc(temp, "init_path");
		free(path[i]);
		path[i] = temp;
		i++;
	}
	return (path);
}
