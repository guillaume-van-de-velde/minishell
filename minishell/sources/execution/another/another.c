/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   another.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:18:50 by svan-de-          #+#    #+#             */
/*   Updated: 2023/04/05 19:18:50 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

void	close_file(int fd)
{
	if (fd < 3)
		return ;
	close(fd);
}

void	close_all(t_pipeline pipeline)
{
	int				i;
	t_heredoc_fds	*heredoc_fds;

	i = 0;
	while (pipeline.commands[i].is_end)
	{
		close_file(pipeline.commands[i].output_file);
		close_file(pipeline.commands[i].input_file);
		close_file(pipeline.commands[i].close_pipe[0]);
		close_file(pipeline.commands[i].close_pipe[1]);
		i++;
	}
	heredoc_fds = get_heredoc_fds_data(NULL);
	close_heredoc_fds(heredoc_fds);
}

void	duplicate_for_streams(t_command *command)
{
	if (dup2(command->input_file, 0) == -1
		|| dup2(command->output_file, 1) == -1)
		perror("minishell: dup2");
	close_all(get_pipeline_singleton(NULL));
}

void	error_command(char *arguments)
{
	char	*str;

	g_status = 127;
	str = ft_strjoin("minishell: `", arguments);
	if (!str)
		return (g_status = ENOMEM, perror("minishell:"));
	str = strjoin_handler(str, "': command not found\n");
	if (!str)
		return (g_status = ENOMEM, perror("minishell:"));
	ft_putstr_fd(str, 2);
	free(str);
}

void	another_command(t_command *command)
{
	char	*path;
	char	**env;

	env = *(environnement(NULL));
	if (!valide_argument_for_path(command->arguments[0]))
		return (error_command(command->arguments[0]));
	if (valide_command(command->arguments[0]))
		path = ft_strdup(command->arguments[0]);
	else
		path = path_for_execve(env, command->arguments[0]);
	if (!path)
	{
		free(path);
		path = NULL;
		return (error_command(command->arguments[0]));
	}
	duplicate_for_streams(command);
	if (execve(path, command->arguments, env) == -1)
	{
		ft_putstr_fd("minishell: execve failed\n", 2);
		(free(path), path = NULL);
	}
}
