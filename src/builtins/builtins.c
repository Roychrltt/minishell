/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:21:31 by xiaxu             #+#    #+#             */
/*   Updated: 2024/09/06 17:42:42 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	return (0);
}

static int	ft_exit(t_mem *mem)
{
	(void)mem;
	return (1);
}

int	do_builtins(t_token *arg, t_mem *mem)
{
	if (!ft_strcmp(arg->value, "echo"))
		return (ft_echo(arg, mem));
	else if (!ft_strcmp(arg->value, "cd"))
		return (ft_cd(mem->my_env, mem->values, arg));
	else if (!ft_strcmp(arg->value, "pwd"))
		return (ft_pwd(mem->values));
	else if (!ft_strcmp(arg->value, "export"))
		return (ft_export(mem->values, arg));
	else if (!ft_strcmp(arg->value, "unset"))
		return (ft_unset(mem->my_env, mem->values, arg));
	else if (!ft_strcmp(arg->value, "env"))
		return (ft_env(mem->my_env));
	else if (!ft_strcmp(arg->value, "exit"))
		return (ft_exit(mem));
	else
		return (0);
}
