/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:19:21 by xiaxu             #+#    #+#             */
/*   Updated: 2024/09/09 18:12:55 by xiaxu            ###   ########.fr       */
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

void	get_exit_stat(char *s, t_mem *mem)
{
	if (is_builtins(s))
		return ;
	if (WIFSIGNALED(mem->status))
		mem->exit_stat = 128 + WTERMSIG(mem->status);
	else if (WIFEXITED(mem->status))
		mem->exit_stat = WEXITSTATUS(mem->status);
	else if (WIFSTOPPED(mem->status))
		mem->exit_stat = 128 + WSTOPSIG(mem->status);
	if (mem->exit_stat == 128 + SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", 2);
	else if (mem->exit_stat == 128 + SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
	}
}

static void	end_execution(t_mem *mem, int num)
{
	int		i;

	i = 0;
	while (i <= num)
	{
		waitpid(mem->pids[i], &(mem->status), 0);
		i++;
	}
	dup2(mem->saved_stdin, STDIN_FILENO);
	dup2(mem->saved_stdout, STDOUT_FILENO);
	free(mem->pids);
}

int	execute(t_mem *mem)
{
	t_token	*temp;
	int		pipe_num;

	temp = mem->tokens;
	if (!expand(&(mem->tokens), mem->values, mem))
		return (0);
	pipe_num = count_pipes(temp);
	mem->pids = malloc((pipe_num + 1) * sizeof (pid_t *));
	if (!mem->pids)
		return (0);
	mem->index = 0;
	while (mem->index < pipe_num)
	{
		ft_command(temp, mem);
		while (!is_end_command(temp))
			temp = temp->next;
		temp = temp->next;
		(mem->index)++;
	}
	last_child(temp, mem);
	end_execution(mem, pipe_num);
	get_exit_stat(mem->last_cmd, mem);
	return (1);
}
