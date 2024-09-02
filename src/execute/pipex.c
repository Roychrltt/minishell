/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:41:50 by xiaxu             #+#    #+#             */
/*   Updated: 2024/09/02 22:54:18 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_args(t_token *list)
{
	t_token	*temp;
	int		i;

	temp = list;
	i = 0;
	while (!is_end_command(temp))
	{
		if (temp->type == ARGUMENT || temp->type == SINGLEQUOTE
			|| temp->type == DOUBLEQUOTE)
			i++;
		temp = temp->next;
	}
	return (i);
}

int	exec_command(t_cmd *cmd, t_token **list, t_mem *mem)
{
	int	i;

	i = 0;
	cmd->count = count_args(*list);
	cmd->args = malloc(sizeof(char *) * (cmd->count + 1));
	while (!is_end_command(*list))
	{
		if ((*list)->type == ARGUMENT || (*list)->type == SINGLEQUOTE
			|| (*list)->type == DOUBLEQUOTE)
		{
			cmd->args[i] = ft_strdup((*list)->value);
			if (!cmd->args[i])
				return (free_tab(cmd->args), 0);
			i++;
		}
		*list = (*list)->next;
	}
	cmd->args[i] = NULL;
	execve(cmd->command, cmd->args, mem->envp);
	perror("execve failure");
	return (0);
}

void	ft_child(t_token **list, t_mem *mem)
{
	t_cmd	cmd;
	pid_t	pid;

	redirect((*list), &cmd);
	while ((*list)->type != COMMAND)
		(*list) = (*list)->next;
	cmd.command = get_command(mem->paths, (*list)->value);
	if (pipe(cmd.fd) == -1)
		perror("Pipe error");
	pid = fork();
	if (pid < 0)
		perror("Fork error");
	if (pid == 0)
	{
		close(cmd.fd[0]);
		dup2(cmd.fd[1], STDOUT_FILENO);
		close(cmd.fd[1]);
		exec_command(&cmd, list, mem);
	}
	else
	{
		close(cmd.fd[1]);
		dup2(cmd.fd[0], STDIN_FILENO);
		close(cmd.fd[0]);
	}
}

void	last_child(t_token **list, t_mem *mem)
{
	t_cmd	cmd;
	pid_t	pid;

	redirect((*list), &cmd);
	while ((*list)->type != COMMAND)
		(*list) = (*list)->next;
	cmd.command = get_command(mem->paths, (*list)->value);
	pid = fork();
	if (pid < 0)
		perror("Fork error");
	if (pid == 0)
	{
		dup2(cmd.fd[1], STDOUT_FILENO);
		close(cmd.fd[1]);
		exec_command(&cmd, list, mem);
	}
	close(cmd.fd[1]);
}
/*
int	pipex(int count, char **tokens, char **envp)
{
	int		i;
	int		infile;
	int		outfile;

	if (!ft_strcmp(tokens[0], "<<"))
	{
		if (argc < 6)
			exit_handler_here_doc();
		i = 3;
		infile = get_here_doc_input(tokens);
	}
	else
	{
		i = 2;
		infile = open_file(argv[1], 0);
	}
	outfile = open_file(argv[argc - 1], 1);
	dup2(infile, STDIN_FILENO);
	close(infile);
	while (i < argc - 2)
		ft_pipe(argv[i++], envp);
	last_child(outfile, argc, argv, envp);
	result_handler(argc);
}*/
