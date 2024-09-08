/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:40:25 by xiaxu             #+#    #+#             */
/*   Updated: 2024/09/08 13:31:24 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

int	g_pid = 0;

static void	begin_of_all(t_mem *mem, char **argv, char **envp)
{
	if (!getenv("PATH"))
	{
		printf("Error: Shut down due to lack of environment variables\n");
		exit(0);
	}
	sig_init_signals();
	mem->saved_stdin = dup(STDIN_FILENO);
	mem->saved_stdout = dup(STDOUT_FILENO);
	mem->argv = argv;
	mem->exit_stat = 0;
	mem->envp = envp;
	mem->values = sort_env(envp);
	mem->my_env = env_dup(envp);
}

static int	init_mem(t_mem *mem)
{
	if (!check_quotes(mem->input))
	{
		mem->exit_stat = 2;
		return (free(mem->input), 0);
	}
	mem->word = 0;
	mem->status = 0;
	mem->count = count_token(mem->input, mem);
	mem->args = tokenizer(mem->input, mem);
	if (!mem->args)
		return (free(mem->input), 0);
	if (!check_metas(mem->args))
	{
		mem->exit_stat = 2;
		return (free(mem->input), free_tab(mem->args), 0);
	}
	mem->paths = get_paths(mem->my_env);
	if (!mem->paths)
		return (free(mem->input), free_tab(mem->args), 0);
	mem->tokens = tokens_to_list(mem->args);
	if (!mem->tokens)
		return (free(mem->input), free_tab(mem->args), free_tab(mem->paths), 0);
	return (1);
}

static void	free_mem(t_mem *mem)
{
	free(mem->input);
	free_tab(mem->args);
	free_tab(mem->paths);
	free_tokens(mem->tokens);
}

static void	end_of_all(t_mem *mem)
{
	close(mem->saved_stdin);
	close(mem->saved_stdout);
	free_env(mem->values);
	free_env(mem->my_env);
	rl_clear_history();
}

int	main(int argc, char **argv, char **envp)
{
	t_mem	mem;

	if (argc > 1)
		return (printf("Error: Too many arguments\n"), 1);
	begin_of_all(&mem, argv, envp);
	while (1)
	{
		mem.input = readline("minishell$>");
		if (!mem.input || !ft_strcmp(mem.input, "exit"))
		{
			free(mem.input);
			printf("exit\n");
			break ;
		}
		if (*(mem.input))
			add_history(mem.input);
		if (!init_mem(&mem))
			continue ;
		if (mem.tokens)
			execute(&mem);
		free_mem(&mem);
	}
	end_of_all(&mem);
	return (0);
}
