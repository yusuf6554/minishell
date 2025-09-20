/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 21:53:55 by ehabes            #+#    #+#             */
/*   Updated: 2025/09/20 13:03:10 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "../lib/libft/libft.h"

# define PROMPT "minishell$ "
# define MAX_PATH 4096
# define MAX_ARGS 1024

/* Çıkış kodları */
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define EXIT_MISUSE 2
# define EXIT_CANT_EXEC 126
# define EXIT_NOT_FOUND 127
# define EXIT_SIGINT 130

/* Lexical analiz için token tipleri */
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_APPEND,
	TOKEN_REDIRECT_HEREDOC,
	TOKEN_EOF
}	t_token_type;

/* Yönlendirme tipleri */
typedef enum e_redirect_type
{
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_APPEND,
	REDIRECT_HEREDOC
}	t_redirect_type;

/* Parsing için token yapısı */
typedef struct s_token
{
	char				*value;
	t_token_type		type;
	struct s_token		*next;
}	t_token;

/* Yönlendirme yapısı */
typedef struct s_redirect
{
	t_redirect_type		type;
	char				*file;
	int					fd;
	struct s_redirect	*next;
}	t_redirect;

/* Komut yapısı */
typedef struct s_cmd
{
	char				**argv;
	t_redirect			*redirects;
	struct s_cmd		*next;
}	t_cmd;

/* Pipeline yapısı */
typedef struct s_pipeline
{
	t_cmd				*commands;
	int					cmd_count;
}	t_pipeline;

/* Environment değişken yapısı */
typedef struct s_env_var
{
	char				*name;
	char				*value;
	struct s_env_var	*next;
}	t_env_var;

/* Ana shell bağlamı */
typedef struct s_minishell
{
	char				**env;
	int					exit_status;
	int					in_heredoc;
	pid_t				*pids;
	int					pid_count;
}	t_minishell;

extern volatile sig_atomic_t	g_signal;

/* Hafıza yardımcıları */

/* Güvenli free */
void		ft_free(void **ptr);
/* Güvenli string free */
void		free_string(char *str);
/* String array'ini temizle */
void		free_string_array(char **arr);
/* Array eleman sayısı */
int			count_string_array(char **arr);
/* Array'i kopyala */
char		**copy_string_array(char **arr);
/* Pids'i temizle */
void		free_pids(pid_t *pids);

/* Environment yardımcıları */

/* Env değişken değeri al */
char		*ft_getenv(char *name, char **env);
/* Env değişken ekle */
char		**env_add_var(char **env, char *name, char *value);
/* Env değişken sil */
char		**env_remove_var(char **env, char *name);
/* Env'i kopyala */
char		**env_copy(char **env);
/* Env'i temizle */
void		env_free(char **env);
/* Env değişken indexi */
int			env_find_index(char **env, char *name);
/* Env değişken adı validasyonu */
int			env_validate_name(char *name);
/* Env değişken ayarla */
int			set_env_var(char ***env, char *name, char *value);

/* Hata yönetimi */

/* Hata mesajı yazdır */
void		error_msg(char *cmd, char *arg, char *msg);
/* System error yazdır */
void		perror_msg(char *cmd);
/* Syntax hatası */
int			syntax_error(char *token);
/* Komut bulunamadı hatası */
void		command_not_found(char *cmd);

/* Debug yardımcıları (geliştirme için) */

/* Token'ları yazdır */
void		print_tokens(t_token *tokens);
/* Pipeline yazdır */
void		print_pipeline(t_pipeline *pipeline);
/* Env'i yazdır */
void		print_env(char **env);

/* Ana shell döngüsü */

/* Ana fonksiyon */
int			main(int argc, char **argv, char **envp);
/* Shell döngüsü */
void		shell_loop(t_minishell *ms);
/* Input oku */
char		*read_input(void);
/* Boş input kontrolü */
int			is_empty_input(char *input);

/* Başlatma ve temizleme */

/* Shell başlatma */
void		init_shell(char **envp, t_minishell *ms);
/* Shell temizleme */
void		cleanup_shell(t_minishell *ms);

#endif
