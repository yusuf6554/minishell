/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:18:24 by yukoc             #+#    #+#             */
/*   Updated: 2025/05/28 14:19:16 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

/* Tokenizer fonksiyonları */
t_token		*tokenize(char *input);              // Input'u token'lara ayır
t_token		*create_token(char *value, t_token_type type);  // Yeni token oluştur
void		free_tokens(t_token *tokens);        // Token'ları temizle

/* Parser fonksiyonları */
t_pipeline	*parse_pipeline(t_token *tokens);    // Token'ları pipeline'a çevir
t_cmd		*parse_command(t_token **tokens);    // Tek komutu parse et
void		free_pipeline(t_pipeline *pipeline); // Pipeline'ı temizle
void		free_command(t_cmd *cmd);            // Komutu temizle

/* Genişletici fonksiyonları */
char		*expand_variables(char *str, char **env);  // $VAR expansion
char		*get_env_value(char *name, char **env);    // Env değişken değeri al
int			is_valid_var_char(char c);               // Geçerli değişken karakteri mi

/* Sinyal yönetimi */
void		setup_signals(void);                 // Signal handler'ları kur
void		setup_child_signals(void);          // Child process signalleri
void		handle_sigint(int sig);              // Ctrl-C handler
void		handle_sigquit(int sig);             // Ctrl-\ handler

#endif