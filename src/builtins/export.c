/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:59:05 by xiaxu             #+#    #+#             */
/*   Updated: 2024/08/25 18:06:49 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_valid_for_export(char *s)
{
	int	i;
	int	j;

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

t_env	*add_env(char *s, t_env **env)
{
	t_env	*node;
	t_env	*temp;

	node = env_new_node(s);
	if (!node)
		return (NULL);
	if (!*env || !(*env)->key)
		return (*env = node, node);
	if (ft_strcmp(node->key, (*env)->key) < 0)
	{
		node->next = *env;
		*env = node;
		return (*env);
	}
	temp = *env;
	while (temp)
	{
		if (!ft_strcmp(node->key, temp->key))
		{
			free(temp->value);
			temp->value = ft_strdup(node->value);
			return (free(node), NULL);
		}
		if (!temp->next || ft_strcmp(node->key, temp->next->key) < 0)
			break ;
		temp = temp->next;
	}
	node->next = temp->next;
	temp->next = node;
	return (node);
}

static int	ft_print_export(t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (temp->is_unset == 0)
		{
			if (ft_strcmp(temp->value, "") > 0)
				printf("export %s=\"%s\"\n", temp->key, temp->value);
			else
				printf("export %s\n", temp->key);
		}
		temp = temp->next;
	}
	return (1);
}

int	ft_export(t_env *env, char **tokens)
{
	size_t	i;

	i = 1;
	if (!tokens[1])
		return (ft_print_export(env));
	while (tokens[i])
	{
		if (is_valid_for_export(tokens[i]))
		{
			add_env(tokens[i], &env);
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

int	ft_unset(t_env *my_env, t_env *values, char **tokens)
{
	t_env	*temp_env;
	t_env	*temp_val;
	int		i;

	i = 0;
	while (tokens[i])
	{
		temp_env = my_env;
		temp_val = values;
		while (temp_env->next)
		{
			if (!ft_strcmp(temp_env->key, tokens[i]))
				temp_env->is_unset = 1;
			temp_env = temp_env->next;
		}
		while (temp_val->next)
		{
			if (!ft_strcmp(temp_val->key, tokens[i]))
				temp_val->is_unset = 1;
			temp_val = temp_val->next;
		}
		i++;
	}
	return (0);
}