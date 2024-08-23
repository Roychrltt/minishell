/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:59:05 by xiaxu             #+#    #+#             */
/*   Updated: 2024/08/21 17:24:45 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_valid_for_export(char* s)
{
	int	i;
	int j;

	if (!ft_isalpha(s[0]) && s[0] != '_')
		return (0);
	i = 0;
	j = ft_strchr(s, '=');
	while (i < j)
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	add_env(char *s, t_env *env)
{
	t_env	*node;
	int		i;

	node = malloc(sizeof (t_env));
	if (!node)
		return (0);
	i = ft_strchr(s, '=');
	node->key = ft_substr(s, 0, i);
	node->value = ft_substr(s, i + 1, ft_strlen(s));
	node->next = NULL;
	if (!env)
	{
		env = node;
		return (1);
	}
	while (env->next)
	{
		if (ft_strcmp(s, env->next->key) <= 0)
			break;
		env = env->next;
	}
	node->next = env->next;
	env->next = node;
	return (1);
}

int	ft_export(char **tokens, t_env *env)
{
	int	i;
	int x;

	i = 0;
	while (tokens[i])
	{
		x = ft_strchr(tokens[i], '=');
		if (is_valid_for_export(tokens[i]))
		{
			add_env(tokens[i], env);
		}
		else
			printf("minishell: export: '%s': not a valid identifier\n",
					tokens[i]);
		i++;
	}
	return (1);
}
