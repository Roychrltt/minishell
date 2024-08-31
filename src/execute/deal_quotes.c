/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 16:08:37 by xiaxu             #+#    #+#             */
/*   Updated: 2024/08/31 17:41:53 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*my_strjoin(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*res;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	res = malloc(len1 + len2 + 1);
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1, len1 + 1);
	ft_strlcpy((res + len1), s2, len2 + 1);
	free(s1);
	return (res);
}

static char	*expansion(char *str, t_env *env)
{
	char	*s;
	char	*sub;
	size_t	i;
	size_t	n;
	size_t	len;

	s = ft_strdup("");
	if (!s)
		return (NULL);
	n = ft_strchr(str, '$');
	len = ft_strlen(str);
	i = n;
	sub = ft_substr(str, 0, i);
	s = my_strjoin(s, sub);
	if (!s)
		return (free(str), free(sub), NULL);
	while (i < len)
	{
		sub = ft_substr(str, 0, i);
		s = my_strjoin(s, sub);
		if (!s)
			return (free(str), free(sub), NULL);
		if (str[i] == '$')
		{
			sub = my_getenv(key, env);
		}
		else
		{}
		n = ft_strchr(str + i, '$');
		i += n;
	}
	free(str);
	return (s);
}

int	deal_quotes(t_token	**list, t_env *env)
{
	t_token	*temp;
	char	*s;

	temp = *list;
	while (temp)
	{
		if (temp->type == SINGLEQUOTE || temp->type == DOUBLEQUOTE)
		{
			s = ft_substr(temp->value, 1, ft_strlen(temp->value) - 2);
			if (!s)
				return (0);
		}
		if (temp->type == DOUBLEQUOTE)
		{
			s = expansion(s, env)
			if (!s)
				return (0);
		}
		free(temp->value);
		temp-value = s;
		temp = temp->next;
	}
	return (1);
}
