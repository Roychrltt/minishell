/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:19:21 by xiaxu             #+#    #+#             */
/*   Updated: 2024/09/08 02:35:58 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_pipes(t_token *list)
{
	int		num;
	t_token	*temp;

	num = 0;
	temp = list;
	while (temp)
	{
		if (!ft_strcmp(temp->value, "|"))
			num++;
		temp = temp->next;
	}
	return (num);
}

int	execute(t_mem *mem)
{
	t_token	*temp;
	int		i;
	int		pipe_num;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	temp = mem->tokens;
	if (!expand(&temp, mem->values, mem))
		return (0);
	i = 0;
	pipe_num = count_pipes(temp);
	while (i < pipe_num)
	{
		ft_command(temp, mem);
		while (!is_end_command(temp))
			temp = temp->next;
		temp = temp->next;
		i++;
	}
	last_child(temp, mem);
	i = 0;
	while (i <= pipe_num)
	{
		wait(&mem->status);
		i++;
	}
	dup2(mem->saved_stdin, STDIN_FILENO);
	dup2(mem->saved_stdout, STDOUT_FILENO);
	get_exit_stat("", mem);
	return (1);
}
