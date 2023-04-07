/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:18:17 by svan-de-          #+#    #+#             */
/*   Updated: 2023/04/05 19:18:17 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

void	exit_process(t_pipeline pipeline, t_blocks *blocks)
{
	char	**env;

	free_pipeline(pipeline);
	env = *(environnement(NULL));
	free_str_arr(env);
	rl_clear_history();
	free(blocks->line_ptr);
	blocks->line_ptr = NULL;
	close_heredoc_fds(blocks->heredoc_ptr);
	free(blocks->heredoc_ptr);
	blocks->heredoc_ptr = NULL;
	exit(g_status);
}
