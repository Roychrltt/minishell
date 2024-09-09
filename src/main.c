/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:40:25 by xiaxu             #+#    #+#             */
/*   Updated: 2024/09/09 14:49:03 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

int	g_pid = 0;

int	main(int argc, char **argv, char **envp)
{
	t_mem	mem;

	if (argc > 1)
		return (printf("Error: Too many arguments\n"), 1);
	begin_of_all(&mem, argv, envp);
	while (1)
	{
		sig_init_signals();
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
