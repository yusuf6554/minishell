/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehabes <ehabes@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:18:24 by yukoc             #+#    #+#             */
/*   Updated: 2025/05/30 01:27:11 by ehabes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

/* Tokenizer fonksiyonları */
t_token		*tokenize(char *input);
t_token		*create_token(char *value, t_token_type type);
void		free_tokens(t_token *tokens);

/* Parser fonksiyonları */
t_pipeline	*parse_pipeline(t_token *tokens);
t_cmd		*parse_command(t_token **tokens);
void		free_pipeline(t_pipeline *pipeline);
void		free_command(t_cmd *cmd);

/* Genişletici fonksiyonları */
char		*expand_variables(char *str, char **env);
char		*get_env_value(char *name, char **env);
int			is_valid_var_char(char c);

/* Sinyal yönetimi */
void		setup_signals(void);
void		setup_child_signals(void);
void		handle_sigint(int sig);
void		handle_sigquit(int sig);

#endif