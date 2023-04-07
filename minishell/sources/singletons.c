/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singletons.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:46:40 by stde-la-          #+#    #+#             */
/*   Updated: 2023/04/06 18:08:20 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_heredoc_data	get_heredoc_data(t_heredoc_data *curr)
{
	static t_heredoc_data	data;

	if (curr)
		data = *curr;
	return (data);
}

t_heredoc_fds	*get_heredoc_fds_data(t_heredoc_fds *curr)
{
	static t_heredoc_fds	*data;

	if (curr)
		data = curr;
	return (data);
}

t_pipeline	get_pipeline_singleton(t_pipeline *pipeline)
{
	static t_pipeline	singleton_pipeline;

	if (pipeline)
		singleton_pipeline = *pipeline;
	return (singleton_pipeline);
}

char	***environnement(char **new_env)
{
	static char	**env = NULL;

	if (new_env)
		env = new_env;
	return (&env);
}
