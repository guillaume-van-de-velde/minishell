/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:37:39 by svan-de-          #+#    #+#             */
/*   Updated: 2023/04/06 19:09:32 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

void			exit_process(t_pipeline pipeline, t_blocks *blocks);
int				exit_max(char *value, char *max);
int				exit_min(char *value, char *min);
int				strcmp_for_exit(char *value, char *min, char *max);
long			ft_atoi_exit(char *str);
int				exit_ms(t_command *command);

int				directory_exist(char *dir);
void			env_ms(t_command *command);

void			delete_variable(char **env, int j);
int				valid_delete(char *argument);
void			delete_env(t_command *command, int i);
void			unset_ms(t_command *command);

void			replace_variable(char **new, char *argument, int lign);
int				is_variable(char **new, char *argument);
void			complete_env(char **new, char **arguments, int i);
int				validate_variable(char *argument);
int				variable_count(char **arguments);
char			**new_env(char **env, char **arguments);
void			export_ms(t_command *command);

void			pwd_ms(t_command *command);

char			*getenv_ms(char *variable);
void			complete_env_pwd(t_command *command, char *old_pwd, char *pwd);
void			env_pwd(char *old_pwd);
void			cd_ms(t_command *command);

int				validate_option(t_command *command, int *i);
void			validate_n(t_command *command, int *i);
void			close_file(int fd_out);
void			echo_ms(t_command *command);

void			free_split(char **split);
void			*free_path(char **paths, char *fill_path, char *final_path);
char			*good_path(char **paths, char *fill_path, char *final_path,
					char *cmd);
char			*find_path(char	*env, char *cmd);
char			*path_for_execve(char **env, char *cmd);

int				valide_argument_for_path(char *argument);
int				valide_command(char *argument);

void			duplicate_for_streams(t_command *command);
int				valide_argument_for_path(char *argument);
void			another_command(t_command *command);

void			execution_env(t_command *command);
void			execution_command(t_command *command);

void			set_position(t_command *commands);
void			set_pipe(t_command *command, int fd[2]);
void			set_files(t_command *command, int link[2], int fd);
int				multi_pipes(t_command *commands, int *fd);

void			pipeline_start(t_command *commands, int fd[2]);
int				fork_command(t_command *command, int i);
int				until_last_command(t_command *commands, int fd[2]);
int				is_child(t_command command);
void			call_to_waitpid(t_command *commands, int i);
void			end_of_pipeline(t_command *commands, int fd[2], int end);

void			execution_pipeline(t_command *commands);

int				bigarray_len(char **bigarray);
void			free_dup(char **dup_bigarray);
char			**duplicate_bigarray(char **bigarray);

void			child_sigint(int sig);
void			child_sigquit(int sig);
void			child_signals(void);
void			signal_for_wait(void);

t_pipeline		get_pipeline_singleton(t_pipeline *pipeline);
void			execute_pipeline(t_pipeline pipeline, t_blocks *blocks);
t_heredoc_fds	*get_heredoc_fds_data(t_heredoc_fds *curr);

#endif