/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:00:37 by xiaxu             #+#    #+#             */
/*   Updated: 2024/08/30 17:49:16 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
			break ;
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
			break ;
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
			break ;
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
			break ;
		}
		temp = temp->next;
	}
}

int	ft_cd(t_env *my_env, t_env *values, t_token *arg)
{
	t_token	*temp;

	temp = arg->next;
	if (is_end_command(arg->next))
	{
		printf("minishell: cd: too few arguments\n");
		return (1);
	}
	if (chdir(temp->value) == -1 && (is_end_command(temp->next)))
	{
		printf("minishell: cd : %s: No such file or directory\n", temp->value);
		return (1);
	}
	if (ft_strlen(arg->next->next->value))
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
