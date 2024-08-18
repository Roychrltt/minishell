/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:45:48 by xiaxu             #+#    #+#             */
/*   Updated: 2024/08/18 16:36:38 by xiaxu            ###   ########.fr       */
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
# include <../libft/libft.h>

extern pid_t	g_pid;

# define PATH "/home/xiaxu/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin"

typedef struct s_mem
{
	int	exit_stat;
}	t_mem;

int		ft_echo(char **s, t_mem *mem);
char	*ft_getenv(char *path, char **envp);
char	*get_command(char *path, char *cmd);
void	free_tab(char **tab);
int		open_file(char *file, int n);
int		open_here_doc(void);
void	result_handler(int argc);

#endif
