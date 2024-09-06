/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:37:27 by xiaxu             #+#    #+#             */
/*   Updated: 2024/09/06 13:26:38 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_pipe(char *str, char **tokens, int *i, int *k)
{
	if (str[*i] == '|')
	{
		tokens[*k] = malloc(sizeof(char) * 3);
		tokens[*k][0] = '|';
		*i += 1;
		tokens[*k][1] = 0;
		if (str[*i] == '|')
		{
			tokens[*k][1] = '|';
			*i += 1;
			tokens[*k][2] = 0;
		}
		*k += 1;
	}
}

static void	skip_redir2(char *str, char **tokens, int *i, int *k)
{
	int	l;

	if (str[*i] == '<')
	{
		l = 0;
		tokens[*k] = malloc(sizeof(char) * 3);
		tokens[*k][l++] = str[*i];
		*i += 1;
		if (str[*i] == '<')
			tokens[*k][l++] = str[(*i)++];
		tokens[*k][l] = 0;
		*k += 1;
	}
	else if (str[*i] == '>')
	{
		l = 0;
		tokens[*k] = malloc(sizeof(char) * 3);
		tokens[*k][l++] = str[*i];
		*i += 1;
		if (str[*i] == '>')
			tokens[*k][l++] = str[(*i)++];
		tokens[*k][l] = 0;
		*k += 1;
	}
}

static void	skip_ampersand(char *str, char **tokens, int *i, int *k)
{
	if (str[*i] == '&' && str[*i + 1] == '&')
	{
		tokens[*k] = malloc(sizeof(char) * 3);
		tokens[*k][0] = '&';
		*i += 2;
		tokens[*k][1] = '&';
		tokens[*k][2] = 0;
		*k += 1;
	}
	else if (str[*i] == ' ')
		while (str[*i] == ' ')
			*i += 1;
}

static void	tokenizer_help(char *str, char **tokens, int *i, int *j, int *k)
{
	int	l;

	l = 0;
	if (*j > 0)
		tokens[*k] = malloc(sizeof(char) * (*j + 1));
	while (l < *j)
	{
		tokens[*k][l] = str[*i - *j + l];
		l++;
	}
	if (*j > 0)
	{
		tokens[*k][l] = 0;
		*k += 1;
	}
}

char	**tokenizer(char *str, t_mem *mem)
{
	int		i;
	int		j;
	int		k;
	char	**tokens;

	i = 0;
	k = 0;
	tokens = malloc(sizeof(char *) * (count_token(str, mem) + 1));
	while (str[i])
	{
		j = 0;
		while (str[i] == ' ')
			i++;
		quote_skip2(str, &i, &j, mem);
		tokenizer_help(str, tokens, &i, &j, &k);
		if (str[i] == '|')
			skip_pipe(str, tokens, &i, &k);
		else if (str[i] == '>' || str[i] == '<')
			skip_redir2(str, tokens, &i, &k);
		else if (str[i] == '&' || str[i] == ' ')
			skip_ampersand(str, tokens, &i, &k);
	}
	tokens[k] = 0;
	return (tokens);
}
