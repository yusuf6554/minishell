/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehabes <ehabes@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:20:17 by yukoc             #+#    #+#             */
/*   Updated: 2025/05/30 01:26:24 by ehabes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

/* Ana yürütücü */
int		execute_pipeline(t_pipeline *pipeline, char ***env);
int		execute_command(t_cmd *cmd, char ***env);
int		execute_single_command(t_cmd *cmd, char ***env);

/* Process yönetimi */
pid_t	create_process(void);
int		wait_for_processes(pid_t *pids, int count);
char	*find_executable(char *cmd, char **env);

/* Pipe yönetimi */
int		setup_pipes(t_cmd *commands);
void	close_pipes(int **pipes, int count);
int		**create_pipes(int count);

/* Yönlendirme yönetimi */
int		setup_redirections(t_redirect *redirects);
int		handle_input_redirect(char *file);
int		handle_output_redirect(char *file, int append);
int		handle_heredoc(char *delimiter);

/* Dahili komutlar */
int		is_builtin(char *cmd);
int		execute_builtin(char **argv, char ***env);
int		builtin_echo(char **argv);
int		builtin_cd(char **argv, char ***env);
int		builtin_pwd(void);
int		builtin_export(char **argv, char ***env);
int		builtin_unset(char **argv, char ***env);
int		builtin_env(char **env);
int		builtin_exit(char **argv);

#endif