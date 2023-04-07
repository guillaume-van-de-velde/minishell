/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:18:36 by svan-de-          #+#    #+#             */
/*   Updated: 2023/04/05 21:40:39 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

void	pwd_ms(t_command *command)
{
	char	*str;

	g_status = 0;
	str = getcwd(NULL, 1024);
	if (!str)
	{
		if (errno == ERANGE)
			perror("minishell: pwd");
		else if (errno == ENOMEM)
			ft_putstr_fd(MEM, 2);
	}
	else
		ft_putstr_fd(str, command->output_file);
	ft_putchar_fd('\n', command->output_file);
	free(str);
	str = NULL;
}
