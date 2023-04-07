/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_heredoc_fds.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:51:18 by stde-la-          #+#    #+#             */
/*   Updated: 2023/04/06 18:10:43 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_heredoc_fds_ins(t_heredoc_fds *heredoc_fds)
{
	if (!heredoc_fds)
		return ;
	while (!heredoc_fds->is_end)
	{
		if (heredoc_fds->fds[1] > 2)
			close(heredoc_fds->fds[1]);
		heredoc_fds->fds[1] = 0;
		heredoc_fds++;
	}
}

void	close_heredoc_fds_outs(t_heredoc_fds *heredoc_fds)
{
	if (!heredoc_fds)
		return ;
	while (!heredoc_fds->is_end)
	{
		if (heredoc_fds->fds[0] > 2)
			close(heredoc_fds->fds[0]);
		heredoc_fds->fds[0] = 0;
		heredoc_fds++;
	}
}

void	close_heredoc_fds(t_heredoc_fds *heredoc_fds)
{
	if (!heredoc_fds)
		return ;
	while (!heredoc_fds->is_end)
	{
		if (heredoc_fds->fds[0] > 2)
			close(heredoc_fds->fds[0]);
		heredoc_fds->fds[0] = 0;
		if (heredoc_fds->fds[1] > 2)
			close(heredoc_fds->fds[1]);
		heredoc_fds->fds[1] = 0;
		heredoc_fds++;
	}
}
