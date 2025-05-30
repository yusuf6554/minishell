/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehabes <ehabes@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:20:17 by yukoc             #+#    #+#             */
/*   Updated: 2025/05/30 01:42:50 by ehabes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

/* Ana yürütücü */
/* Pipeline'ı çalıştır */
int		execute_pipeline(t_pipeline *pipeline, char ***env);
/* Tek komutu çalıştır */
int		execute_command(t_cmd *cmd, char ***env);
/* Basit komut çalıştır */
int		execute_single_command(t_cmd *cmd, char ***env);

/* Process yönetimi */
/* Yeni process oluştur */
pid_t	create_process(void);
/* Process'leri bekle */
int		wait_for_processes(pid_t *pids, int count);
/* PATH'te executable bul */
char	*find_executable(char *cmd, char **env);

/* Pipe yönetimi */
/* Pipe'ları kur */
int		setup_pipes(t_cmd *commands);
/* Pipe'ları kapat */
void	close_pipes(int **pipes, int count);
/* Pipe array'i oluştur */
int		**create_pipes(int count);

/* Yönlendirme yönetimi */
/* Redirection'ları kur */
int		setup_redirections(t_redirect *redirects);
/* Input redirection */
int		handle_input_redirect(char *file);
/* Output redirection */
int		handle_output_redirect(char *file, int append);
/* Heredoc işle */
int		handle_heredoc(char *delimiter);

/* Dahili komutlar */
/* Built-in komut mu kontrol et */
int		is_builtin(char *cmd);
/* Built-in komutu çalıştır */
int		execute_builtin(char **argv, char ***env);
/* echo komutu */
int		builtin_echo(char **argv);
/* cd komutu */
int		builtin_cd(char **argv, char ***env);
/* pwd komutu */
int		builtin_pwd(void);
/* export komutu */
int		builtin_export(char **argv, char ***env);
/* unset komutu */
int		builtin_unset(char **argv, char ***env);
/* env komutu */
int		builtin_env(char **env);
/* exit komutu */
int		builtin_exit(char **argv);

#endif