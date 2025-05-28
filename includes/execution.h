/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:20:17 by yukoc             #+#    #+#             */
/*   Updated: 2025/05/28 14:20:28 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

/* Ana yürütücü */
int			execute_pipeline(t_pipeline *pipeline, char ***env);  // Pipeline'ı çalıştır
int			execute_command(t_cmd *cmd, char ***env);            // Tek komutu çalıştır
int			execute_single_command(t_cmd *cmd, char ***env);     // Basit komut çalıştır

/* Process yönetimi */
pid_t		create_process(void);                     // Yeni process oluştur
int			wait_for_processes(pid_t *pids, int count);  // Process'leri bekle
char		*find_executable(char *cmd, char **env);     // PATH'te executable bul

/* Pipe yönetimi */
int			setup_pipes(t_cmd *commands);             // Pipe'ları kur
void		close_pipes(int **pipes, int count);      // Pipe'ları kapat
int			**create_pipes(int count);                // Pipe array'i oluştur

/* Yönlendirme yönetimi */
int			setup_redirections(t_redirect *redirects);    // Redirection'ları kur
int			handle_input_redirect(char *file);           // Input redirection
int			handle_output_redirect(char *file, int append);  // Output redirection
int			handle_heredoc(char *delimiter);              // Heredoc işle

/* Dahili komutlar */
int			is_builtin(char *cmd);                    // Built-in komut mu kontrol et
int			execute_builtin(char **argv, char ***env);  // Built-in komutu çalıştır
int			builtin_echo(char **argv);                // echo komutu
int			builtin_cd(char **argv, char ***env);     // cd komutu
int			builtin_pwd(void);                        // pwd komutu
int			builtin_export(char **argv, char ***env); // export komutu
int			builtin_unset(char **argv, char ***env);  // unset komutu
int			builtin_env(char **env);                  // env komutu
int			builtin_exit(char **argv);                // exit komutu

#endif