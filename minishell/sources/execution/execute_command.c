/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:18:54 by svan-de-          #+#    #+#             */
/*   Updated: 2023/04/05 19:18:54 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

void	execution_env(t_command *command)
{
	if (!command->arguments || !command->arguments[0]
		|| !command->arguments[0][0])
		return (g_status = 0, (void)0);
	if (!ft_strncmp(command->arguments[0], "cd", 3))
		return (cd_ms(command));
	if (!ft_strncmp(command->arguments[0], "export", 7))
		return (export_ms(command));
	if (!ft_strncmp(command->arguments[0], "unset", 6))
		return (unset_ms(command));
}

void	execution_command(t_command *command)
{
	if (!command->arguments || !command->arguments[0])
		return (g_status = 0, (void)0);
	if (!command->arguments[0][0])
		return (g_status = 127,
			ft_putstr_fd("minishell: '': command not found\n", 2));
	if (!ft_strncmp(command->arguments[0], "cd", 3))
		return (cd_ms(command));
	if (!ft_strncmp(command->arguments[0], "export", 7))
		return (export_ms(command));
	if (!ft_strncmp(command->arguments[0], "unset", 6))
		return (unset_ms(command));
	if (!ft_strncmp(command->arguments[0], "exit", 5))
		return ((void)exit_ms(command));
	if (!ft_strncmp(command->arguments[0], "echo", 5))
		return (echo_ms(command));
	if (!ft_strncmp(command->arguments[0], "pwd", 4))
		return (pwd_ms(command));
	if (!ft_strncmp(command->arguments[0], "env", 4))
		return (env_ms(command));
	another_command(command);
}
