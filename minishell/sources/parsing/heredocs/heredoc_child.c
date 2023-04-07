/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 22:07:13 by stde-la-          #+#    #+#             */
/*   Updated: 2023/04/05 21:45:26 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

void	exit_heredoc(int sig)
{
	t_heredoc_data	heredoc;

	if (sig == SIGINT)
		ft_putstr_fd("\n", 1);
	heredoc = get_heredoc_data(NULL);
	free_str_arr(*(environnement(NULL)));
	close_heredoc_fds(heredoc.heredoc_fds);
	free(heredoc.heredoc_fds);
	heredoc.heredoc_fds = NULL;
	free_str_arr(heredoc.limits);
	rl_clear_history();
	exit(0);
}

void	heredoc_child(char *limit, int fd)
{
	int	status;

	signal(SIGINT, exit_heredoc);
	status = read_user_input(fd, limit);
	if (status == ENOMEM)
		perror("minishell: malloc");
	else if (status == -1)
	{
		ft_putstr_fd("minishell: warning: ", 2);
		ft_putstr_fd("here-document delimited by end-of-file (wanted `", 2);
		ft_putstr_fd(limit, 2);
		ft_putstr_fd("')\n", 2);
	}
	exit_heredoc(0);
}
