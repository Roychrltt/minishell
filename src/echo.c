/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:23:17 by xiaxu             #+#    #+#             */
/*   Updated: 2024/08/21 17:12:51 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	char	*pwd;

	pwd = getenv("PWD");
	if (!pwd)
	{
		perror("minishell: pwd: error retrieving current working directory");
		return (1);
	}
	printf("%s\n", pwd);
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

int	ft_env(t_env *env)
{
	if (!env)
		return (1);
	while (env)
	{
		printf("%s=\"%s\"", env[i]->key, env[i]->value);
		env = env->next;
	}
	return (0);
}
