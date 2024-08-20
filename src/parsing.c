/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:24:34 by xiaxu             #+#    #+#             */
/*   Updated: 2024/08/20 14:56:41 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	free_tokens(char **tokens)
{
	int i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

static void	print_tokens(char **tokens)
{
	int i = 0;
	while (tokens[i])
	{
		printf("%s", tokens[i++]);
		if (tokens[i])
			printf(" ");
	}
	free_tokens(tokens);
}

int main(int argc, char **argv)
{
	if (argc != 2)
		printf("Wrong number of argument!\n");

	char **tokens;
	if ((ft_strchr(argv[1], '"') == ft_strlen(argv[1])) && (ft_strchr(argv[1], 39) == ft_strlen(argv[1])))
	{
		tokens = ft_split(argv[1], ' ');
		print_tokens(tokens);
		return (0);
	}

	int i;
	int s;
	int d;
	int status = 0;

	i = 0;
	while (argv[1][i])
	{
		s = ft_strchr(argv[1] + i, 39);
		d = ft_strchr(argv[1] + i, '"');
		if (status == 0 || s < d)
		{
			status = 1;
			tokens = ft_split(ft_substr(argv[1], i, s), ' ');
			print_tokens(tokens);
			i += s;
		}
		else if (status == 0 || d < s)
		{
			status = 2;
			tokens = ft_split(ft_substr(argv[1], i, d), ' ');
			print_tokens(tokens);
			i += d;
		}
		else if (status == 1)
		{
			while (s--)
			{
				write (1, &argv[1][i], 1);
				i++;
			}
		}
		else if (status == 2)
		{
			while (d)
			{
				while (d-- && argv[1][i] != '$')
				{
					write (1, &argv[1][i], 1);
					i++;
				}
				if (d > 0)
				{
					printf("set_value\n");
					while (argv[1][i] >= 'A' && argv[1][i] <= 'Z')
					{
						i++;
						d--;
					}
				}
			}
		}
		else
		{
			tokens = ft_split(ft_substr(argv[1], i, ft_strlen(argv[1]) - i), ' ');
			print_tokens(tokens);
			break;
		}
		i++;
	}
	return 0;
}
