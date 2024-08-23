/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:23:17 by xiaxu             #+#    #+#             */
/*   Updated: 2024/08/23 17:28:31 by xiaxu            ###   ########.fr       */
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

int	ft_pwd(t_env *env)
{
	char	*pwd;
	t_env	*temp;

	pwd = NULL;
	temp = env;
	while (temp)
	{
		if (!ft_strcmp(temp->key, "PWD"))
		{
			pwd = temp->value;
			break;
		}
		temp = temp->next;
	}
	if (!pwd)
	{
		perror("minishell: pwd: error retrieving current working directory");
		return (1);
	}
	printf("%s\n", pwd);
	return (0);
}

int	ft_cd(t_env *env, char **tokens)
{
	t_env	*temp;
	if (ft_strlen(tokens[2]))
	{
		printf("ok\n");
		//printf("%zu\n", ft_strlen(tokens[2]));
		printf("minishell: cd: too many arguments\n");
		return (1);
	}
	chdir(tokens[1]);
	temp = env;
	while (temp)
	{
		if (!ft_strcmp(temp->key, "PWD"))
		{
			free(temp->value);
			temp->value = getcwd(NULL, 0);
			break;
		}
		temp = temp->next;
	}
	return (0);
}

int	ft_env(t_env *env)
{
	t_env	*temp;

	temp = env;
	if (!env || !env->key)
		return (1);
	printf("entered env\n");
	while (temp)
	{
		if (!temp->is_unset)
			printf("%s=\"%s\"\n", temp->key, temp->value);
		temp = temp->next;
	}
	return (0);
}

int	ft_unset(t_env *env, char **tokens)
{
	t_env	*temp;
	int		i;

	i = 0;
	while (tokens[i])
	{
		temp = env;
		while (temp->next)
		{
			if (!ft_strcmp(temp->key, tokens[i]))
			{
				temp->is_unset = 1;
				break;
			}
			temp = temp->next;
		}
		i++;
	}
	return (0);
}
