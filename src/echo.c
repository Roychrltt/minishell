/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:23:17 by xiaxu             #+#    #+#             */
/*   Updated: 2024/08/24 12:53:13 by xiaxu            ###   ########.fr       */
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

static void	update_oldpwd(t_env *env)
{
	t_env	*temp;
	char	*s;

	temp = env;
	s = NULL;
	while (temp)
	{
		if (!ft_strcmp(temp->key, "PWD"))
		{
			s = temp->value;
			break;
		}
		temp = temp->next;
	}
	temp = env;
	while (temp)
	{
		if (!ft_strcmp(temp->key, "OLDPWD") && s)
		{
			free(temp->value);
			temp->value = ft_strdup(s);
			break;
		}
		temp = temp->next;
	}
}

static void	update_pwd(t_env *env)
{
	t_env	*temp;

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
}

int	ft_cd(t_env *my_env, t_env *values, char **tokens)
{
	if (chdir(tokens[1]) == -1 && !tokens[2])
	{
		printf("minishell: cd : %s: No such file or directory\n", tokens[1]);
		return (1);
	}
	if (ft_strlen(tokens[2]))
	{
		printf("minishell: cd: too many arguments\n");
		return (1);
	}
	update_oldpwd(my_env);
	update_oldpwd(values);
	update_pwd(my_env);
	update_pwd(values);
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
