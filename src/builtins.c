/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:21:31 by xiaxu             #+#    #+#             */
/*   Updated: 2024/08/21 16:24:49 by xiaxu            ###   ########.fr       */
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

int	do_builtins(char *s, t_mem *mem, char **tokens)
{
	if (!ft_strcmp(s, "echo"))
		return (ft_echo(tokens, mem));
	else if (!ft_strcmp(s, "cd"))
		return (ft_cd(tokens));
	else if (!ft_strcmp(s, "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(s, "export"))
		return (ft_export(tokens, mem->env));
	else if (!ft_strcmp(s, "unset"))
		return (ft_unset(params, args));
	else if (!ft_strcmp(s, "env"))
		return (ft_env(envp));
/*	else if (!ft_strcmp(s, "exit"))
		return (ft_exit(params, args));*/
	else
		return (0);
}
