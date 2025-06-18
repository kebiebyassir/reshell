#ifndef MINISHELL_H
# define MINISHELL_H

# include "../utils/ft_printf/printf.h"
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <unistd.h>
# include <errno.h>

// environnement struct
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

// garbage collector struct
typedef struct s_gc_list
{
	void				*ptr;
	struct s_gc_list	*next;
}	t_gc_list;

typedef struct s_gc
{
	t_gc_list	*head;
}	t_gc;

// Token types
typedef enum
{
	WORD,            // normal string
	PIPE,            // |
	REDIRECT_IN,     // <
	REDIRECT_OUT,    // >
	REDIRECT_APPEND, // >>
	HEREDOC,         // <<
	T_EOF              // EOF
}					t_token_type;

// token struct
typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}					t_token;

// lexer struct
typedef struct s_lexer
{
	char			*input;
	int				pos;
	int				len;
}					t_lexer;

// parsing struct
typedef struct s_cmd
{
	char **args;             // command + arguments
	char *input_file;        // for < redirection
	char *output_file;       // for > redirection
	int append_mode;         // for >> (1 = append, 0 = overwrite)
	char *heredoc_delimiter; // for << redirection
	int	is_ambiguous;        // for ambiguous redirect (0 or 1)
	int has_redirection;     // redirection or not (0 or 1)
	struct s_cmd *next;      // for pipes
}					t_cmd;

// duplicate environnement
t_env	*create_env(char *envp);
t_env	*dup_env(char **envp);
void	free_env(t_env	*env);
void	print_env(t_env *env);

// garbage collector
void	gc_init(t_gc *gc);
void	*gc_saver(void *p, t_gc *gc);
void	*gc_malloc(size_t size, t_gc *gc);
void	gc_free(t_gc *gc);

// execution
char	*get_path(char *cmd, t_env *env_list);
int 	check_per(t_cmd *cmd, t_env *env_list);
int		is_builtin(t_cmd *cmds);
void	execute_builtin(t_cmd *cmds, t_env *env_list);
void	execute_command(t_cmd *cmds, char **envp, t_env *env_list);
int		redirection_out(t_cmd *cmd, t_env *env_list, char **envp);

// builtins



// // lexer and tokenization
// t_lexer	*init_lexer(char	*input, t_gc *gc);
// int		is_special_char(char c);
// char	*read_word(t_lexer *lexer, t_gc *gc);
// t_token	*create_token(t_token_type type, char *value, t_gc *gc);
// void	skip_whitespace(t_lexer *lexer);
// t_token	*get_next_token(t_lexer	*lexer, t_gc *gc);
// t_token	*tokenize(char	*input, t_gc *gc);

// // parsing
// t_cmd	*init_cmd(t_gc *gc);
// char	*get_env_value(t_env *env, char *key);
// char	*expand_variable(char *str, t_env *env, t_gc *gc);
// int		add_arg_to_cmd(t_cmd *cmd, char *arg, t_env *env, t_gc *gc);
// int		handle_redirection(t_cmd *cmd, t_token **myToken);
// t_cmd	*parse_command(t_token **tokens, t_env *env, t_gc *gc);
// t_cmd	*parse_tokens(t_token *tokens, t_env *env, t_gc *gc);
// int		validate_tokens(t_token *tokens);


// utils
char	**ft_split(const char *s, char c);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_isdigit(int c);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
char	*ft_strdup_gc(const char *s, t_gc *gc);
char	*ft_strdup(const char *s);
char	*ft_strjoin(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strlen(const char *s);
char	*ft_strtok(char *str, const char *delim, int *index);
char	*ft_substr(const char *s, size_t start, size_t len);
char	*ft_strncpy(char *dest, const char *src, size_t n);
int		ft_atoi(const char *str);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_realloc(void *ptr, size_t size, t_gc *gc);
void	*ft_memset(void *str, int n, size_t len);
void	ft_bzero(void *str, size_t n);
void	*ft_calloc(size_t count, size_t size);

#endif
