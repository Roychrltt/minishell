/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 18:30:27 by xiaxu             #+#    #+#             */
/*   Updated: 2024/08/25 19:38:17 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_token	*gen_new_token(char	*s, int start, int len, int type)
{
	t_token	*node;

	node = malloc(sizeof (t_token));
	if (!node)
		return (NULL);
	node->value = ft_substr(s, start, len);
	if (!node->value)
		return (free(node), NULL);
	node->type = type;
	node->next = NULL;
	return (node);
}

static void	add_back(t_token *list, t_token *node)
{
	t_token	*temp;

	temp = list;
	if (!list)
		list = node;
	while (temp)
	{
		if (!temp->next)
		{
			temp->next = node;
			break ;
		}
		temp = tmep->next;
	}
}

t_token	*tokenize(char *s)
{
	t_token	*tokens;
	char	**t;
	size_t	i;
	size_t	next;
	size_t	x;
	size_t	y;

	tokens = NULL;
	i = 0;
	while (s[i])
	{
		next = next_quote(s);

	}
}
