/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:40:25 by xiaxu             #+#    #+#             */
/*   Updated: 2024/08/25 14:55:27 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

int	g_pid = 0;

static t_env	*copy_env(char **envp)
{
	t_env	*list;
	t_env	*temp;
	int		i;

	list = NULL;
	temp = NULL;
	i = 0;
	while (envp[i])
	{
		temp = add_env(envp[i], &list);
		if (!list)
			list = temp;
		i++;
	}
	return (list);
}

static int	init_mem(t_mem *mem, char **envp)
{
	mem->exit_stat = 0;
	mem->values = copy_env(envp);
	mem->my_env = env_dup(envp);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_mem	mem;

	(void)argc, (void)argv;
	char	*input;
	init_mem(&mem, envp);
	sig_init_signals();
	while (1)
	{
		input = readline("minishell$>");
		mem.input = input;
		if (!input || !ft_strcmp(input, "exit"))
		{
			printf("exit\n");
			break;
		}
		if (*input)
			add_history(input);
		mem.tokens = ft_split(input, ' ');
		mem.token = ft_tokenize(input);
		if (is_builtins(mem.tokens[0]))
			do_builtins(mem.tokens[0], &mem, mem.tokens);
		free(input);
		free_tab(mem.tokens);
	}
	rl_clear_history();
	return (0);
}
