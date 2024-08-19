/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:21:31 by xiaxu             #+#    #+#             */
/*   Updated: 2024/08/19 16:44:40 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtins(char *s)
{
	if (!s)
		return (0);
	if (!ft_strcmp(s, "echo") || !ft_strcmp(s, "cd") || !ft_strcmp(s, "pwd")
			|| !ft_strcmp(s, "export") || !ft_strcmp(s, "unset")
			|| !ft_strcmp(s, "env"))
		return (1);
	if (!ft_strcmp(s, "exit"))
		return (2);
	else
		return (0);
}

int	ft_echo(char **s, t_mem *mem)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	if (s[1] && !ft_strcmp(s[1], "-n"))
		n = 1;
	if (n)
		i++;
	while (s[i])
	{
		if ((n && i > 2) || (!n && i > 1))
			printf(" ");
		printf("%s", s[i]);
		i++;
	}
	if (!n || i == 1)
		printf("\n");
	mem->exit_stat = 0;
	return (1);
}

int	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("minishell: pwd: error retrieving current working directory");
		return (1);
	}
	printf("%s\n", cwd);
	return (0);
}

int	ft_cd(char **tokens)
{
	if (tokens[2])
		return (ft_putstr_fd("minishell: cd: too many arguments\n",
					STDERR_FILENO), 1);
	chdir(tokens[1]);
	return (0);
}

int	ft_env(char **envp)
{
	int	i;

	i = 0;
	if (!envp || !(*envp))
		return (1);
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}

int	do_builtins(char *s, t_mem *mem, char **tokens, char **envp)
{
	if (!ft_strcmp(s, "echo"))
		return (ft_echo(tokens, mem));
	else if (!ft_strcmp(s, "cd"))
		return (ft_cd(tokens));
	else if (!ft_strcmp(s, "pwd"))
		return (ft_pwd());
	/*	else if (!ft_strcmp(s, "export"))
		return (ft_export(params, args));
		else if (!ft_strcmp(s, "unset"))
		return (ft_unset(params, args));*/
		else if (!ft_strcmp(s, "env"))
		return (ft_env(envp));
	/*	else if (!ft_strcmp(s, "exit"))
		return (ft_exit(params, args));*/
	else
		return (0);
}
