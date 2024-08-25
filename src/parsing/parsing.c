/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:21:43 by xiaxu             #+#    #+#             */
/*   Updated: 2024/08/25 18:05:44 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_tokenize(char *s)
{

}
int	infile_n;
int double_quote_n;
int single_quote_n;

while (s[i] == ' ')
	i++;

if (s[i] == '|')
{
	type = Pipe;
	i++;
}

if (s[i] == '<' && s[i + 1] != '<')
{
	type = REDIRECT_IN;
	i++;
}

if (s[i] == '<' && s[i + 1] == '<')
{
	type = HEREDOC;
	i += 2;
}

if (s[i] == '>' && s[i + 1] != '>')
{
	type = REDIRECT_OUT;
	i++;
}

if (s[i] == '>' && s[i + 1] == '>')
{
	type = APPEND;
	i += 2;
}

if (s[i] == '\'')
{
	type = SINGLEQUOTE;
	if (single_quote_n == 0)
		single_quote_n = 1;
	else
		single_quote_n = 0;
	i++;
}

if (s[i] == '\"')
{
	type = DOUBLEQUOTE;
	if (double_quote_n == 0)
		double_quote_n = 1;
	else
		double_quote_n = 0;
	i++;
}

if (single_quote_n || double_quote_n)
	return (printf("minishell: invalid input: quotes not closed\n"), 1);
