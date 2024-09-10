/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:40:25 by xiaxu             #+#    #+#             */
/*   Updated: 2024/09/10 17:19:20 by xiaxu            ###   ########.fr       */
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
		if (!mem.input)
			break ;
		if (*(mem.input))
			add_history(mem.input);
		if (!init_mem(&mem))
			continue ;
		if (mem.tokens)
			execute(&mem);
		free_mem(&mem);
		if (mem.exit == 1)
			break ;
	}
	end_of_all(&mem);
	printf("exit\n");
	return (mem.exit_stat);
}
