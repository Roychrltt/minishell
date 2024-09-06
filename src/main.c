/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:40:25 by xiaxu             #+#    #+#             */
/*   Updated: 2024/09/06 18:24:43 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

int	g_pid = 0;

static void	begin_of_all(t_mem *mem, char **argv, char **envp)
{
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
		return (free(mem->input), 0);
	mem->found = 0;
	mem->squote = 0;
	mem->dquote = 0;
	mem->word = 0;
	mem->count = count_token(mem->input, mem);
	mem->args = tokenizer(mem->input, mem);
	if (!mem->args)
		return (0);
	mem->paths = get_paths(mem->my_env);
	if (!mem->paths)
		return (free_tab(mem->args), 0);
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
	free_env(mem->values);
	free_env(mem->my_env);
	close(mem->saved_stdin);
	close(mem->saved_stdout);
	rl_clear_history();
}

int	main(int argc, char **argv, char **envp)
{
	t_mem	mem;

	(void)argc;
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
		if (!init_mem(&mem))
			continue ;
		if (*(mem.input))
			add_history(mem.input);
		mem.tokens = tokens_to_list(mem.args);
		if (mem.tokens)
			execute(&mem);
		free_mem(&mem);
	}
	end_of_all(&mem);
	return (0);
}
