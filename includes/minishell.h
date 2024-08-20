/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:45:48 by xiaxu             #+#    #+#             */
/*   Updated: 2024/08/20 14:25:44 by xiaxu            ###   ########.fr       */
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

/*typedef enum e_token_type
{
	INFILE,
	OUTFILE,
	HEREDOC,
	N_HEREDOC,
	APPEND,
	REDIRECT_IN;,
	REDIRECT_OUT,
	PIPE,
	STRING,
	SINGLEQUOTE,
	DOUBLEQUOTE,
	COMMAND,
	FILENAME,
	ARGUMENT
}	t_token_type;*/

typedef struct s_mem
{
	int	exit_stat;
}	t_mem;
/*
typedef struct s_token
{
	char			*value;
//	t_params		*params;
	t_token_type	type;
	struct s_token	*next;
}	t_token;
*/
int		is_builtins(char *s);
//int		do_builtins(char *s, t_params *params, char **tokens);
int		do_builtins(char *s, t_mem *mem, char **tokens, char **envp);

int		ft_echo(char **s, t_mem *mem);
int		ft_pwd(void);
int		ft_cd(char **tokens);
int		ft_env(char **envp);
char	*ft_getenv(char *path, char **envp);
char	*get_command(char *path, char *cmd);
void	free_tab(char **tab);
int		open_file(char *file, int n);
int		open_here_doc(void);
void	result_handler(int argc);

void	sig_init_signals(void);
void	sigint_handler(int signum);

#endif
