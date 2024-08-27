/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 15:54:32 by xiaxu             #+#    #+#             */
/*   Updated: 2024/08/27 20:23:00 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	index_n(char *s, char *c, int n)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_strncmp(s + i, c, ft_strlen(c)))
			n--;
		if (n <= 0)
			return (i);
		i++;
	}
	return (i);
}

size_t	next_quote(char *s)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '"')
			break;
		i++;
	}
	while (s[j])
	{
		if (s[j] == '\'')
			break;
		j++;
	}
	if (i > j)
		i = j;
	return (i);
}

int	set_quotes_n(char c, int *quotes_n)
{
	int	cquotes;

	cquotes = *quotes_n;
	if (c == '\'')
	{
		if (cquotes == 0)
			*quotes_n = 1;
		else if (cquotes == 1)
			*quotes_n = 0;
	}
	if (c == '"')
	{
		if (cquotes == 0)
			*quotes_n = 2;
		else if (cquotes == 2)
			*quotes_n = 0;
	}
	return (cquotes);
}

int	check_quotes(char *s)
{
	int	i;
	int	quote_n;

	i = 0;
	quote_n = 0;
	while (s[i])
	{
		set_quotes_n(s[i], &quote_n);
		i++;
	}
	if (quote_n != 0)
		return (printf("minishell: invalid input: quotes not closed\n"), 1);
	return (0);
}

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

int	check_meta_next(char *s1, char *s2)
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
