/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/03 13:40:41 by rcappend      #+#    #+#                 */
/*   Updated: 2022/03/07 14:16:32 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <parser.h>
# include <fcntl.h>

# define READ 0
# define WRITE 1
# define CHILD 0
# define NO_PIPE -1

/*
	Global variable that indicates what minishell is currently doing
*/
int	g_state;
# define EXECUTING 0
# define COMMAND 1
# define HEREDOC_INPUT 2

typedef struct s_fork
{
	pid_t			pid;
	struct s_fork	*next;
}	t_fork;

void		executor(t_cmd *cmd, t_mini_vars *vars);
int			exec_forked_cmd(t_fork *new_fork, t_cmd *cmd, \
			t_mini_vars *vars, int fd);
void		execute_cmd(t_cmd *cmd, t_exec *exec, t_mini_vars *vars);
char		**init_paths(char **env);
int			init_heredoc(t_cmd *cmd);
int			here_doc(char *delim);
int			redirect_input(t_red *input, int fd, t_mini_vars *vars);
int			redirect_output(t_red *output, int fd, t_mini_vars *vars);
int			file_error(const char *filename);

int			built_in(t_cmd *cmds, char *cmd, t_mini_vars *vars);
int			is_special_builtin(char *cmd);

void		sigquit_handler(int signum);

#endif