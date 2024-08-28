/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_metas.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:15:55 by xiaxu             #+#    #+#             */
/*   Updated: 2024/08/28 14:17:58 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_meta_char(char *s)
{
	if (!ft_strcmp(s, "<"))
		return (REDIRECT_IN);
	if (!ft_strcmp(s, ">"))
		return (REDIRECT_OUT);
	if (!ft_strcmp(s, "<<"))
		return (HEREDOC);
	if (!ft_strcmp(s, ">>"))
		return (APPEND);
	if (!ft_strcmp(s, "&&"))
		return (AND);
	if (!ft_strcmp(s, "||"))
		return (OR);
	if (!ft_strcmp(s, "|"))
		return (PIPE);
	return (0);
}

int	is_redirect(char *s)
{
	if (!ft_strcmp(s, "<"))
		return (REDIRECT_IN);
	if (!ft_strcmp(s, ">"))
		return (REDIRECT_OUT);
	if (!ft_strcmp(s, "<<"))
		return (HEREDOC);
	if (!ft_strcmp(s, ">>"))
		return (APPEND);
	return (0);
}

int	is_logical(char *s)
{
	if (!ft_strcmp(s, "&&"))
		return (AND);
	if (!ft_strcmp(s, "||"))
		return (OR);
	return (0);
}

static int	check_meta_next(char *s1, char *s2)
{
	if (is_redirect(s1))
	{
		if (is_meta_char(s2))
		{
			printf("minishell: parse error near \'%s\'", s2);
			return (0);
		}
	}
	else
	{
		if (!ft_strcmp(s2, "|") || is_logical(s2))
		{
			printf("minishell: parse error near \'%s\'", s1);
			return (0);
		}
	}
	return (1);
}

int	check_metas(char **tokens)
{
	int	i;

	i = 0;
	if (!ft_strcmp(tokens[0], "|") || is_logical(tokens[0]))
		return (printf("minishell: syntax error near \'%s\'", tokens[0]), 0);
	while (tokens[i + 1])
	{
		if (is_meta_char(tokens[i]))
		{
			if (!check_meta_next(tokens[i], tokens[i + 1]))
				return (0);
		}
		i++;
	}
	if (is_meta_char(tokens[i]))
		return (printf("minishell: syntax error near \'%s\'", tokens[i]), 0);
	return (1);
}
