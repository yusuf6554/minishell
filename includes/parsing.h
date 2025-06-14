/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:18:24 by yukoc             #+#    #+#             */
/*   Updated: 2025/06/04 22:51:08 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

/* Tokenizer fonksiyonları */
/* Input'u token'lara ayır */
t_token		*tokenize(char *input);
/* Yeni token oluştur */
t_token		*create_token(char *value, t_token_type type);
/* Token'ları temizle */
void		free_tokens(t_token **tokens);

/* Parser fonksiyonları */
/* Token'ları pipeline'a çevir */
t_pipeline	*parse_pipeline(t_token *tokens);
/* Tek komutu parse et */
t_cmd		*parse_command(t_token **tokens);
/* Pipeline'ı temizle */
void		free_pipeline(t_pipeline **pipeline);
/* Komutu temizle */
void		free_command(t_cmd *cmd);

/* Genişletici fonksiyonları */
/* $VAR expansion */
char		*expand_variables(char *str, char **env);
/* Env değişken değeri al */
char		*get_env_value(char *name, char **env);
/* Geçerli değişken karakteri mi */
int			is_valid_var_char(char c);

/* Sinyal yönetimi */
/* Signal handler'ları kur */
void		setup_signals(void);
/* Child process signalleri */
void		setup_child_signals(void);
/* Ctrl-C handler */
void		handle_sigint(int sig);
/* Ctrl-\ handler */
void		handle_sigquit(int sig);

#endif