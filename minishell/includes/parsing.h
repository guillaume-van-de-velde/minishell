/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 13:09:17 by stde-la-          #+#    #+#             */
/*   Updated: 2023/04/06 17:06:57 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define RED_ERROR 2
# define WILDSTAR 1

# include "minishell.h"

t_heredoc_fds	*handle_heredocs(char *line);
int				get_heredoc_amount(char *line);
char			*get_heredoc_limit(char **line, char *heredoc_limit);
void			heredoc_child(char *limit, int fd);
int				read_user_input(int fd, char *limit);
char			*get_heredoc_limit(char **line, char *heredoc_limit);
t_heredoc_data	get_heredoc_data(t_heredoc_data *curr);

void			skip_pipelines_to_not_execute(char **line, t_pipeline last,
					t_heredoc_fds *heredoc_fds);
void			skip_command(char **line, t_pipeline *pipeline,
					t_heredoc_fds **heredoc_fds);
void			check_last_command_status(t_pipeline *pipeline);

int				get_pipeline(char **line, t_pipeline *pipeline,
					t_heredoc_fds **heredoc_fds);
void			handle_parenthesis(char **line, t_pipeline *pipeline,
					char parenthesis);

char			**get_line_args(char **line, int expand_env_var);
char			**handle_env_var(char **line, int is_inside_quotes);
char			*dup_line_word(char **line);

int				get_pipeline_commands_amount(char *line);
int				get_pipelines_amount(char *line);

int				add_char(char **line, char **str, int is_str_arr);

int				str_arr_size(char **arr);
char			**join_arr_strjoin(char **dest, char **arr2);
char			**join_str_arr(char **dest, char **arr2);
char			**str_arr_dup(char **src);
int				strjoin_str_arr(char **str_arr, char *join);
char			**insert_str_arr_at_index(char **arr1, char **arr2, int index);
void			mem_cpy_str_arr(char **dest, char **src);
void			mem_cpy_str_arr_upto(char **dest, char **src, int up_to);

int				check_syntax(char *line);
int				check_line(char *line, int is_inside_parenthesis,
					char *line_ptr_cpy);
int				check_missing_parenthesis(char **line);
int				check_redirection_error(char **line);
int				check_operator_error(char **line);
int				is_last_special_symbol(char *line);
int				check_for_missing_quote(char *line);
int				check_quotes(char **line);
void			skip_special_symbol(char **line);
int				check_parenthesis_error(char **line, char *ptr,
					int is_inside_parenthesis);

int				is_parenthesis(char *line);
int				is_redirection(char *line);
int				is_pipe(char *line);
int				is_quote(char c);
int				is_env_var(char *line, char quote_type);;
int				is_operator(char *line);
int				is_meta_char(char *line);
int				is_wildcard(char *str);
int				is_heredoc(char *line);
int				is_directory(char *file);
int				is_white_space(char c);
int				is_env_var_heredoc(char *line, char quote_type);
int				is_export_command(t_command *command);
int				has_dot_slash_prefix(char *str);
int				has_slash_prefix(char *str);

int				get_redirections(char **line, t_command *command,
					t_heredoc_fds **heredoc_fds);
int				handle_simple_right_redirection(t_command *command, char *file);
int				handle_simple_left_redirection(t_command *command, char *file);
int				handle_double_right_redirection(t_command *command, char *file);

int				assign_heredoc_fd(char **line, t_command *command,
					t_heredoc_fds **heredoc_fds);

void			skip_spaces(char **line);
void			get_operator(char **line, t_pipeline *pipeline);
int				file_or_dir_check(t_command *command, char *str,
					int access_type);
void			*ft_realloc(void *src, int prev_size, int new_size);

void			print_error(char *message, char *line);
void			print_error_arg(char *message, char *line);
char			*strjoin_handler(char *str, char *join);

char			**handle_widlcards(char **args);
int				compare(char *wildcard, char *file);
char			*parse_wildcard(char *wildcard, t_wildcard_info *wildcard_info);
char			**get_wildcard_matches(char *wildcard);
void			sort(char **arr, int size);
int				is_match(char *curr_dir_wildcard,
					t_wildcard_info *wildcard_info, char *file);
int				wildcard_matches_amount(char *curr_dir_wildcard,
					t_wildcard_info *wildcard_info);
void			replace_chars(char *str, char c, char replace_with);

void			free_pipeline(t_pipeline pipeline);
void			free_str_arr(char **str_arr);
void			close_heredoc_fds_ins(t_heredoc_fds *heredoc_fds);
void			close_heredoc_fds_outs(t_heredoc_fds *heredoc_fds);
void			close_heredoc_fds(t_heredoc_fds *heredoc_fds);

#endif