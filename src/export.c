/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:59:05 by xiaxu             #+#    #+#             */
/*   Updated: 2024/08/23 17:31:34 by xiaxu            ###   ########.fr       */
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

t_env	*add_env(char *s, t_env *env)
{
	t_env	*node;
	t_env	*temp;
	int		i;

	node = malloc(sizeof (t_env));
	if (!node)
		return (0);
	i = ft_strchr(s, '=');
	node->key = ft_substr(s, 0, i);
	node->value = ft_substr(s, i + 1, ft_strlen(s));
	node->is_unset = 0;
	node->next = NULL;
	if (!env)
		return (node);
	temp = env;
	while (temp->next)
	{
		if (ft_strcmp(s, temp->next->key) <= 0)
			break;
		temp = temp->next;
	}
	node->next = temp->next;
	temp->next = node;
	return (node);
}

int	ft_export(t_env *env, char **tokens)
{
	size_t	i;

	i = 1;
	if (!tokens[1])
		return (ft_env(env));
	while (tokens[i])
	{
		if (is_valid_for_export(tokens[i]))
		{
			add_env(tokens[i], env);
		}
		else
		{
			printf("minishell: export: '%s': not a valid identifier\n",
					tokens[i]);
		}
		i++;
	}
	return (1);
}
