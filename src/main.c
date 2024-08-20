/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:40:25 by xiaxu             #+#    #+#             */
/*   Updated: 2024/08/20 18:00:37 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

int	g_pid = 0;

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char	*input;
	char	**tokens;
	t_mem	mem;

	sig_init_signals();
	while (1)
	{
		input = readline("minishell$>");
		if (!input || !ft_strcmp(input, "exit"))
		{
			if (!input)
				printf("exit\n");
			break;
		}
		if (*input)
			add_history(input);
		tokens = ft_split(input, ' ');
		if (is_builtins(tokens[0]))
			do_builtins(tokens[0], &mem, tokens, envp);
		free(input);
	}
	rl_clear_history();
	return (0);
}
