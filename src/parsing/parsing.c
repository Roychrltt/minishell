/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:21:43 by xiaxu             #+#    #+#             */
/*   Updated: 2024/08/25 19:47:21 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	get_type(char *s, char *status)
{
	if (!ft_strcmp(s, "<<"))
		return (HEREDOC);
	if (!ft_strcmp(s, ">>"))
		return (APPEND);
	if (!ft_strcmp(s, ">"))
		return (REDIRECT_OUT);
	if (!ft_strcmp(s, "<"))
		return (REDIRECT_IN);
	if (!ft_strcmp(s, "|"))
		return (PIPE);
	if (!ft_strcmp(s, "&&"))
		return (AND);
	if (!ft_strcmp(s, "||"))
		return (OR);
	if (!ft_strcmp(status, "infile") && !ft_strcmp(s, ">>"))
		return (APPEND);
}
