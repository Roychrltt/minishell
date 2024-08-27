/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:21:43 by xiaxu             #+#    #+#             */
/*   Updated: 2024/08/27 21:32:50 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*parsing(t_var *var)
{
	t_token	*token_list;
	t_token	*temp;
	int		new_cmd;

	if (!check_quotes(var->input) || !check_metas(var->tokens))
		return (NULL);
	token_list = tokens_to_list(var->tokens);
	new_cmd = 0;
	if (is_meta_char(token_list->value))
		token_list->type = is_meta_char(token_list->value);
	else
	{
		token_list->type = COMMAND;
		new_cmd = 1;
	}
	temp = token_list->next;
	while (temp)
	{
		if (is_meta_char(temp->value))
		{
			if (is_logical(temp->value) || !ft_strcmp(temp->value, "|"))
				new_cmd = 0;
			temp->type = is_meta_char(temp->value);
		}
		else if (!ft_strcmp(temp->prev->value, "<"))
			temp->type = INFILE;
		else if (!ft_strcmp(temp->prev->value, "<<"))
			temp->type = N_HEREDOC;
		else if (!ft_strcmp(temp->prev->value, ">"))
			temp->type = OUTFILE;
		else if (!ft_strcmp(temp->prev->value, ">>"))
			temp->type = APPEND;
		else if (new_cmd == 0)
		{
			temp->value = COMMAND;
			new_cmd = 1;
		}
		else
			temp->type = ARGUMENT;
		temp = temp->next;
	}
	return (token_list);
}
