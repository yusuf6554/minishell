/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 21:53:55 by ehabes            #+#    #+#             */
/*   Updated: 2025/05/28 14:23:04 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>              // printf, fprintf
# include <stdlib.h>             // malloc, free, exit
# include <unistd.h>             // fork, execve, pipe, dup2
# include <string.h>             // strcmp, strcpy, strlen
# include <sys/wait.h>           // wait, waitpid
# include <sys/stat.h>           // stat, access
# include <fcntl.h>              // open, close
# include <errno.h>              // error handling
# include <signal.h>             // signal handling
# include <readline/readline.h>  // readline fonksiyonu
# include <readline/history.h>   // history yönetimi

# define PROMPT "minishell$ "     // Shell prompt mesajı
# define MAX_PATH 4096          // Maksimum path uzunluğu
# define MAX_ARGS 1024          // Maksimum argüman sayısı

/* Çıkış kodları */
# define EXIT_SUCCESS 0         // Başarılı çıkış
# define EXIT_FAILURE 1         // Genel hata
# define EXIT_MISUSE 2          // Yanlış kullanım
# define EXIT_CANT_EXEC 126     // Komut çalıştırılamadı
# define EXIT_NOT_FOUND 127     // Komut bulunamadı


/* Lexical analiz için token tipleri */
typedef enum e_token_type
{
	TOKEN_WORD,             // Normal kelime/komut
	TOKEN_PIPE,             // | karakteri
	TOKEN_REDIRECT_IN,      // < karakteri
	TOKEN_REDIRECT_OUT,     // > karakteri
	TOKEN_REDIRECT_APPEND,  // >> karakterleri
	TOKEN_REDIRECT_HEREDOC, // << karakterleri
	TOKEN_EOF               // Input sonu
}	t_token_type;

/* Yönlendirme tipleri */
typedef enum e_redirect_type
{
	REDIRECT_IN,            // Input yönlendirme
	REDIRECT_OUT,           // Output yönlendirme
	REDIRECT_APPEND,        // Append yönlendirme
	REDIRECT_HEREDOC        // Heredoc yönlendirme
}	t_redirect_type;


/* Parsing için token yapısı */
typedef struct s_token
{
	char				*value;     // Token değeri
	t_token_type		type;       // Token tipi
	struct s_token		*next;      // Sonraki token
}	t_token;

/* Yönlendirme yapısı */
typedef struct s_redirect
{
	t_redirect_type		type;       // Redirection tipi
	char				*file;      // Dosya adı
	int					fd;         // File descriptor
	struct s_redirect	*next;      // Sonraki redirection
}	t_redirect;

/* Komut yapısı */
typedef struct s_cmd
{
	char				**argv;     // Komut ve argümanlar
	t_redirect			*redirects; // Redirection listesi
	struct s_cmd		*next;      // Sonraki komut (pipe için)
}	t_cmd;

/* Pipeline yapısı (parser ve executor arası ana arayüz) */
typedef struct s_pipeline
{
	t_cmd				*commands;  // Komut listesi
	int					cmd_count;  // Komut sayısı
}	t_pipeline;

/* Environment değişken yapısı */
typedef struct s_env_var
{
	char				*name;      // Değişken adı
	char				*value;     // Değişken değeri
	struct s_env_var	*next;      // Sonraki değişken
}	t_env_var;

/* Ana shell bağlamı */
typedef struct s_minishell
{
	char				**env;      // Environment değişkenleri
	int					exit_status;// Son komutun çıkış kodu
	int					in_heredoc; // Heredoc durumu
	pid_t				*pids;      // Process ID'leri
	int					pid_count;  // Process sayısı
}	t_minishell;


extern t_minishell	g_shell;    // Global shell yapısı

/*                         YARDIMCI PROTOTİPLER                            */

// (libft)

/* Hafıza yardımcıları */
void		ft_free(void **ptr);                     // Güvenli free
void		free_string_array(char **arr);           // String array'ini temizle
int			count_string_array(char **arr);          // Array eleman sayısı
char		**copy_string_array(char **arr);         // Array'i kopyala

/* Environment yardımcıları */
char		*ft_getenv(char *name, char **env);      // Env değişken değeri al
char		**env_add_var(char **env, char *name, char *value);  // Env değişken ekle
char		**env_remove_var(char **env, char *name);   // Env değişken sil
char		**env_copy(char **env);                     // Env'i kopyala
void		env_free(char **env);                       // Env'i temizle
int			env_find_index(char **env, char *name);     // Env değişken indexi

/* Hata yönetimi */
void		error_msg(char *cmd, char *arg, char *msg);  // Hata mesajı yazdır
void		perror_msg(char *cmd);                      // System error yazdır
int			syntax_error(char *token);                  // Syntax hatası
void		command_not_found(char *cmd);               // Komut bulunamadı hatası

/* Debug yardımcıları (geliştirme için) */
void		print_tokens(t_token *tokens);              // Token'ları yazdır
void		print_pipeline(t_pipeline *pipeline);       // Pipeline yazdır
void		print_env(char **env);                      // Env'i yazdır


/*                              ANA PROTOTİPLER                            */


/* Ana shell döngüsü */
int			main(int argc, char **argv, char **envp);  // Ana fonksiyon
void		shell_loop(void);                          // Shell döngüsü
char		*read_input(void);                         // Input oku
int			is_empty_input(char *input);               // Boş input kontrolü

/* Başlatma ve temizleme */
void		init_shell(char **envp);                   // Shell başlatma
void		cleanup_shell(void);                       // Shell temizleme

#endif