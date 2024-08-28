/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 18:30:27 by xiaxu             #+#    #+#             */
/*   Updated: 2024/08/28 14:22:52 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_token(char *str, t_var *var)
{
	int		i;
	int		j;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		while (str[i] != ' ' && str[i] != '>' && str[i] != '<' && str[i] != '|' && str[i] != '&' && str[i])
		{
			if (str[i] == '\'')
			{
				var->squote = 1;
				i++;
			}
			else if (str[i] == '"')
			{
				var->dquote = 1;
				i++;
			}
			while ((var->squote == 1 || var->dquote == 1) && str[i])
			{
				if (str[i] == '\'' && var->squote == 1)
					var->squote = 0;
				if (str[i] == '"' && var->dquote == 1)
					var->dquote = 0;
				i++;
			}
			if (str[i] != ' ' && str[i] != '>' && str[i] != '<' && str[i] != '|' && str[i])
				i++;
			var->word = 1;
		}
		if (var->word == 1)
		{
			var->word = 0;
			count++;
		}
		if (str[i] == '|')
		{
			count++;
			i++;
			if (str[i] == '|')
				i++;
		}
		else if (str[i] == '<')
		{
			count++;
			i++;
			j = 0;
			while (str[i] == '<' && j++ < 3)
				i++;
		}
		else if (str[i] == '&' && str[i + 1] == '&')
		{
			count++;
			i += 2;
		}
		else if (str[i] == '>')
		{
			count++;
			i++;
			if (str[i] == '>')
				i++;
		}
	}
	return (count);
}

char	**tokenizer(char *str, t_var *var)
{
	int		i;
	int		j;
	int		k;
	int		l;
	char	**tokens;

	i = 0;
	k = 0;
	tokens = malloc(sizeof (char *) * (count_token(str, var) + 1));
	while (str[i])
	{
		j = 0;
		l = 0;
		while (str[i] == ' ')
			i++;
		while (str[i] != ' ' && str[i] != '>' && str[i] != '<' && str[i] != '&' && str[i] != '|' && str[i])
		{
			if (str[i] == '\'')
			{
				var->squote = 1;
				i++;
				j++;
			}
			if (str[i] == '"')
			{
				var->dquote = 1;
				i++;
				j++;
			}
			while ((var->squote == 1 || var->dquote == 1) && str[i])
			{
				if (str[i] == '\'' && var->squote == 1)
					var->squote = 0;
				if (str[i] == '"' && var->dquote == 1)
					var->dquote = 0;
				i++;
				j++;
			}
			if (str[i] != ' ' && str[i] != '>' && str[i] != '<' && str[i] != '|' && str[i])
			{
				i++;
				j++;
			}
		}
		if (j > 0)
			tokens[k] = malloc(sizeof(char) * (j + 1));
		while (l < j)
		{
			tokens[k][l] = str[i - j + l];
			l++;
		}
		if (j > 0)
		{
			tokens[k][l] = 0;
			k++;
		}
		if (str[i] == '|')
		{
			tokens[k] = malloc(sizeof(char) * 3);
			tokens[k][0] = '|';
			i++;
			if (str[i] == '|')
			{
				tokens[k][1] = '|';
				i++;
			}
			tokens[k][2] = 0;
			k++;
		}
		else if (str[i] == '<')
		{
			l = 0;
			tokens[k] = malloc(sizeof(char) * 3);
			tokens[k][l++] = str[i];
			i++;
			while (str[i] == '<')
				tokens[k][l++] = str[i++];
			tokens[k][l] = 0;
			k++;
		}
		else if (str[i] == '&' && str[i + 1] == '&')
		{
			tokens[k] = malloc(sizeof(char) * 3);
			tokens[k][0] = '&';
			i += 2;
			tokens[k][1] = '&';
			tokens[k][2] = 0;
			k++;
		}
		else if (str[i] == '>')
		{
			l = 0;
			tokens[k] = malloc(sizeof(char) * 3);
			tokens[k][l++] = str[i];
			i++;
			if (str[i] == '>')
				tokens[k][l++] = str[i++];
			tokens[k][l] = 0;
			k++;
		}
		else if (str[i] == ' ')
			while (str[i] == ' ')
				i++;
	}
	tokens[k] = 0;
	return (tokens);
}
