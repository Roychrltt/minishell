/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:00:37 by xiaxu             #+#    #+#             */
/*   Updated: 2024/09/09 16:19:01 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(t_env *env, t_mem *mem)
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
	mem->exit_stat = 0;
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

static int	check_cd(t_token *token)
{
	if (is_end_command(token))
	{
		printf("minishell: cd: too few arguments\n");
		return (0);
	}
	if (chdir(token->value) == -1 && (is_end_command(token->next)))
	{
		printf("minishell: cd : %s: No such file or directory\n", token->value);
		return (0);
	}
	if (!is_end_command(token->next))
	{
		printf("minishell: cd: too many arguments\n");
		return (0);
	}
	return (1);
}

int	ft_cd(t_token *arg, t_mem *mem)
{
	if (!check_cd(arg->next))
	{
		mem->exit_stat = 1;
		return (0);
	}
	update_oldpwd(mem->my_env);
	update_oldpwd(mem->values);
	update_pwd(mem->my_env);
	update_pwd(mem->values);
	mem->exit_stat = 0;
	return (1);
}
