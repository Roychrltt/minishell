/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 11:26:27 by xiaxu             #+#    #+#             */
/*   Updated: 2024/08/24 12:10:44 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*env_new_node(char *s)
{
	t_env	*node;
	size_t	i;

	node = malloc(sizeof (t_env));
	if (!node || !s)
		return (NULL);
	i = ft_strchr(s, '=');
	node->key = ft_substr(s, 0, i);
	node->value = ft_substr(s, i + 1, ft_strlen(s));
	node->is_unset = 0;
	node->next = NULL;
	return (node);
}

t_env	*env_dup(char **envp)
{
	t_env	*list;
	t_env	*temp;
	size_t	x;

	list = env_new_node(envp[0]);
	temp = list;
	x = 1;
	while (envp[x])
	{
		temp->next = env_new_node(envp[x]);
		temp = temp->next;
		x++;
	}
	return (list);
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
