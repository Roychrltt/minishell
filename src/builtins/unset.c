/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 17:27:23 by xiaxu             #+#    #+#             */
/*   Updated: 2024/09/01 15:58:18 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*my_getenv(char *key, t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (!ft_strcmp(temp->key, key))
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

int	ft_unset(t_env *my_env, t_env *values, t_token *arg)
{
	t_env	*temp_env;
	t_env	*temp_val;
	t_token	*temp;

	temp = arg->next;
	while (temp && !is_end_command(temp))
	{
		temp_env = my_env;
		temp_val = values;
		while (temp_env)
		{
			if (!ft_strcmp(temp_env->key, temp->value))
				temp_env->is_unset = 1;
			temp_env = temp_env->next;
		}
		while (temp_val)
		{
			if (!ft_strcmp(temp_val->key, temp->value))
				temp_val->is_unset = 1;
			temp_val = temp_val->next;
		}
		temp = temp->next;
	}
	return (0);
}
