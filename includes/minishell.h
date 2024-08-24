/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:45:48 by xiaxu             #+#    #+#             */
/*   Updated: 2024/08/24 15:31:16 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/uio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/signal.h>
# include <errno.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

extern pid_t	g_pid;

typedef enum e_token_type
{
	INFILE,
	OUTFILE,
	HEREDOC,
	N_HEREDOC,
	APPEND,
	REDIRECT_IN,
	REDIRECT_OUT,
	PIPE,
	STRING,
	SINGLEQUOTE,
	DOUBLEQUOTE,
	COMMAND,
	FILENAME,
	ARGUMENT
}	t_token_type;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				is_unset;
	struct s_env	*next;
}	t_env;

typedef struct s_token
{
	char			*value;
//	t_params		*params;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef struct s_mem
{
	int		exit_stat;
	char	*input;
	char	**tokens;
	t_env	*my_env;
	t_env	*values;
}	t_mem;

// builtins
int		is_builtins(char *s);
int		do_builtins(char *s, t_mem *mem, char **tokens);

int		ft_echo(char **s, t_mem *mem);
int		ft_cd(t_env *my_env, t_env *values, char **tokens);
int		ft_pwd(t_env *env);
t_env*	env_new_node(char *s);
t_env*	env_dup(char **envp);
int		ft_env(t_env *env);
t_env	*add_env(char *s, t_env **env);
int		ft_export(t_env *env, char **tokens);
int		ft_unset(t_env *my_env, t_env *values, char **tokens);

// pipex
char	*ft_getenv(char *path, char **envp);
char	*get_command(char *path, char *cmd);
void	free_tab(char **tab);
int		open_file(char *file, int n);
int		open_here_doc(void);
void	result_handler(int argc);

// signals
void	sig_init_signals(void);
void	sigint_handler(int signum);

// utils
void	free_tab(char **tab);

#endif
