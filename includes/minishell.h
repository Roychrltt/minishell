/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:45:48 by xiaxu             #+#    #+#             */
/*   Updated: 2024/08/31 00:01:13 by xiaxu            ###   ########.fr       */
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
	HEREDOC,
	N_HEREDOC,
	APPEND,
	REDIRECT_IN,
	REDIRECT_OUT,
	PIPE,
	AND,
	OR,
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
	char	*input;
	int		found;
	int		squote;
	int		dquote;
	int		word;
	int		count;
	char	**args;
	char	**argv;
	int		exit_stat;
	t_env	*my_env;
	t_env	*values;
	char	**paths;
	t_token	*tokens;
	t_cmd	*cmds;
}	t_mem;

// builtins
int		is_builtins(char *s);
int		do_builtins(t_token *arg, t_mem *mem);

int		ft_echo(t_token *arg, t_mem *mem);
int		ft_cd(t_env *my_env, t_env *values, t_token *arg);
int		ft_pwd(t_env *env);
t_env	*env_new_node(char *s);
t_env	*env_dup(char **envp);
t_env	*sort_env(char **envp);
int		ft_env(t_env *env);
t_env	*add_env(char *s, t_env **env);
void	free_env(t_env *env);
int		ft_export(t_env *env, t_token *arg);
int		ft_unset(t_env *my_env, t_env *values, t_token *arg);

// pipex
int		execute(t_mem *mem);
char	*ft_getenv(char *path, char **envp);
char	*get_command(char *path, char *cmd);
void	free_tab(char **tab);
int		open_file(char *file, int n);
int		open_here_doc(void);
void	result_handler(int argc);

// signals
void	sig_init_signals(void);
void	sigint_handler(int signum);

// ---parsing--- //

// check_quotes
int		index_n(char *s, char *c, int n);
size_t	next_quote(char *s);
int		check_quotes(char *s);

// check_metas
int		is_meta_char(char *s);
int		is_redirect(char *s);
int		is_logical(char *s);
int		is_end_command(t_token *arg);
int		check_metas(char **tokens);

// tokenize
int		count_token(char *str, t_mem *mem);
char	**tokenizer(char *str, t_mem *mem);
t_token	*tokens_to_list(char **tokens);

// token_utils
t_token	*gen_new_token(char	*s);
void	token_add_back(t_token **list, t_token *node);
void	free_tokens(t_token *tokens);

#endif
/*
find the last redirect_in, the value of the next token is the name of the infile
find the last redirect_out, the value of the next token is the name of the outfile
open every file accordingly
then dup2();
then execve();


int fd_in = open(infile, ...);
if (fd_in < 0)

int fd_out = open(outfile, ...);
if (fd_out < 0)
	error_handler();
dup2(fd_in, )*/
