/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/03 13:41:43 by rcappend      #+#    #+#                 */
/*   Updated: 2022/03/07 09:28:39 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <tokens.h>

# define SYNTAX_ERROR -1
# define EXPANDED 1
# define NO_EXPAND 0

typedef struct s_mini_vars
{
	char	**paths;
	char	**env;
	int		last_pid;
}	t_mini_vars;

typedef enum e_red_type {
	RED_IPUT,
	HERE_DOC,
	RED_OPUT,
	RED_OPUT_A
}	t_red_type;

typedef struct s_red {
	t_red_type		type;
	char			*file_name;
	int				heredoc;
	struct s_red	*next;
}	t_red;

typedef struct s_exec {
	char	*cmd;
	char	**args;
	int		len;
}	t_exec;

typedef struct s_cmd {
	t_exec			*exec;
	t_red			*input;
	t_red			*output;
	struct s_cmd	*next;
}	t_cmd;

/*
	command list utils
*/
t_cmd	*new_cmd(void);
void	free_cmd(t_cmd **cmd);
void	*free_cmd_list(t_cmd **ref);
void	add_argument(t_exec *exec, t_token *token);

/*
	redirects list utils
*/
void	free_redirects(t_red *red);
t_red	*new_redirect(t_red_type type);

/*
	main
*/
int		parse_redirects(t_cmd *cmds, t_token **tokens, t_mini_vars *vars);
int		parse_quotes_and_expand(t_token *token, char **env, t_mini_vars *vars);
int		expander(t_token *token, char **env, int last_pid, long i);
int		parse_words(t_cmd *cmd, t_token *tokens, t_mini_vars *vars);
int		syntax_error(const t_type type, t_mini_vars *vars);
t_cmd	*parser(t_token *tokens, char **env, t_mini_vars *vars);
void	resplit_args(t_token *token);

#endif
