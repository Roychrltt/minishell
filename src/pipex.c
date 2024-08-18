/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:41:50 by xiaxu             #+#    #+#             */
/*   Updated: 2024/08/18 16:49:59 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell"

static void	exec_command(char *param, char **envp)
{
	char	*path;
	char	**command_args;
	char	*command;

	command_args = ft_split(param, ' ');
	if (!command_args)
		exit(EXIT_FAILURE);
	path = ft_getenv("PATH", envp);
	command = get_command(path, command_args[0]);
	if (!command)
	{
		free_tab(command_args);
		free(command);
		perror_message("Invalid command.\n");
	}
	execve(command, command_args, envp);
	perror_message("Pipex");
}

static int	get_here_doc_input(char **tokens)
{
	char	*input;
	int		file;

	file = open(".here_doc.tmp", O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR);
	if (file == -1)
		printf(".here_doc.tmp open failure\n");
	write (1, ">", 1);
	while (1)
	{
		input = get_next_line(STDIN_FILENO);
		if (!input)
			printf("Invalid input\n");
		if (ft_strncmp(input, argv[2], ft_strlen(argv[2])) == 0)
		{
			free(input);
			break ;
		}
		write(file, input, ft_strlen(input));
		free(input);
	}
	close(file);
	file = open_here_doc();
	return (file);
}

static void	ft_pipe(char *param, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		perror_message("Pipe");
	pid = fork();
	if (pid == -1)
		perror_message("Fork");
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		exec_command(param, envp);
		perror_message("Pipex");
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
}

static void	last_child(int outfile, int argc, char **argv, char **envp)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		perror_message("Fork");
	if (pid == 0)
	{
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
		exec_command(argv[argc - 2], envp);
	}
	close(outfile);
}

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
}
