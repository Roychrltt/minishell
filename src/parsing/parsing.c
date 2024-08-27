/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:21:43 by xiaxu             #+#    #+#             */
/*   Updated: 2024/08/27 16:39:09 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*parsing(char *input)
{
	t_token	*tokens;
	t_token	*node;
	char	*s;
	int		type;
	int		i;
	int		new_cmd;

	i = 0;
	new_cmd = 1;
	if (!ft_strcmp(src[i], "<"))
		type = REDIRECT_IN;
	else if (!ft_strcmp(src[i], "<<"))
		type = HEREDOC;
	else
		type = COMMAND;
	node = gen_new_token(src[i], type);
	if (!node)
		return (NULL);
	tokens = node;
	i++;
	return (tokens);
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

int	get_type(char *s)
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
//	if (!ft_strcmp(status, "infile") && !ft_strcmp(s, ">>"))
//		return (APPEND);
}
