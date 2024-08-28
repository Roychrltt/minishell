/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:35:18 by xiaxu             #+#    #+#             */
/*   Updated: 2024/08/18 16:35:22 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	open_here_doc(void)
{
	int	fd;

	fd = open(".here_doc.tmp", O_RDONLY);
	if (fd == -1)
	{
		unlink(".here_doc.tmp");
		perror_message(".here_doc.tmp file open failure");
	}
	return (fd);
}

void	result_handler(int argc)
{
	int	i;

	i = 0;
	while (i < argc - 3)
	{
		wait(NULL);
		i++;
	}
	unlink(".here_doc.tmp");
}
