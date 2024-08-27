/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:45:48 by xiaxu             #+#    #+#             */
/*   Updated: 2024/08/27 21:02:37 by xiaxu            ###   ########.fr       */
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
	ARGUMENT,
	INFILE,
	OUTFILE,
	HEREDOC,  // meta
	N_HEREDOC,
	APPEND, // meta
	REDIRECT_IN,  // meta
	REDIRECT_OUT,  // meta
	PIPE,  // meta
	AND, //meta
	OR,  // meta
	SINGLEQUOTE,
	DOUBLEQUOTE,
	COMMAND
}	t_token_type;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				is_unset;
	struct s_env	*next;
}	t_env;

typedef struct s_var
{
	char	*input;
	int		squote;
	int		dquote;
	int		word;
	int		count;
	char	**tokens;
	char	*temp_path;
	char	**path;
	char	**argv;
	int		found;
	t_list	*env;
}	t_var;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_cmd
{
	char	*cmd;
	char	**args;
	int		*fd_in;
	int		*fd_out;
}	t_cmd;

typedef struct s_mem
{
	int		exit_stat;
	char	*input;
	t_token	*tokens;
	t_env	*my_env;
	t_env	*values;
	t_cmd	*cmds;
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

// parsing
int		index_n(char *s, char *c, int n);
size_t	next_quote(char *s);
int		set_quotes_n(char *c, int quotes_n);
int		check_quotes(char *s);
int		is_meta_char(*s);
int		is_redirect(*s);
int		is_logical(*s);
int		check_meta_next(char *s1, char *s2);
int		check_metas(char **tokens);
char	**tokenizer(char *str, t_var *var);
t_token	*tokens_to_list(char **tokens);
t_token	*parsing(t_var *var);

#endif
