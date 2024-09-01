/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 16:08:37 by xiaxu             #+#    #+#             */
/*   Updated: 2024/09/01 15:35:42 by xiaxu            ###   ########.fr       */
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
	if (len1)
		ft_strlcpy(res, s1, len1 + 1);
	if (len2)
		ft_strlcpy((res + len1), s2, len2 + 1);
	if (s1)
		free(s1);
	return (res);
}

static int	is_name_char(int c)
{
	return (ft_isalnum(c) || c == '_');
}

static void	free_t(t_expand *t)
{
	if (t->s)
		free(t->s);
	if (t->sub)
		free(t->sub);
	if (t->key)
		free(t->key);
}

static char	*expansion(char *str, t_env *env)
{
	t_expand	t;

	t.i = 0;
	t.s = ft_strdup("");
	if (!t.s)
		return (free(str), NULL);
	t.len = ft_strlen(str);
	while (t.i < t.len)
	{
		if (str[t.i] == '$' && is_name_char((int)str[t.i + 1]))
		{
			t.n = 0;
			t.i++;
			while (str[t.i + t.n] && is_name_char((int)str[t.i + t.n]))
				t.n++;
			t.key = ft_substr(str, t.i, t.n);
			if (!t.key)
				return (free(str), free(t.s), NULL);
			t.sub = ft_strdup(my_getenv(t.key, env));
			free(t.key);
		}
		else
		{
			t.n = ft_strchr(str + t.i, '$');
			t.sub = ft_substr(str + t.i, 0, t.n);
		}
		if (!t.sub)
			return (free(str), free(t.s), NULL);
		t.s = my_strjoin(t.s, t.sub);
		if (!t.s)
			return (free(str), free(t.sub), NULL);
		free(t.sub);
		t.i += t.n;
	}
	free(str);
	return (t.s);
}

int	deal_quotes(t_token	**list, t_env *env)
{
	t_token	*temp;
	char	*s;

	temp = *list;
	while (temp)
	{
		if (temp->type == SINGLEQUOTE || temp->type == DOUBLEQUOTE)
			s = ft_substr(temp->value, 1, ft_strlen(temp->value) - 2);
		else
			s = ft_strdup(temp->value);
		if (!s)
			return (0);
		if (temp->type == DOUBLEQUOTE || temp->type == ARGUMENT)
			s = expansion(s, env);
		if (!s)
			return (0);
		free(temp->value);
		temp->value = s;
		temp = temp->next;
	}
	return (1);
}
