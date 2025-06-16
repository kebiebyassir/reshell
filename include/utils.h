#ifndef UTILS_H
# define UTILS_H

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

char	**ft_split(const char *s, char c);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_isdigit(int c);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
char	*ft_strdup(const char *s);
char	*ft_strjoin(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strlen(const char *s);
char	*ft_strtok(char *str, const char *delim, int *index);
char	*ft_substr(const char *s, size_t start, size_t len);
char	*ft_strncpy(char *dest, const char *src, size_t n);
int		ft_atoi(const char *str);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_realloc(void *ptr, size_t size);
void	*ft_memset(void *str, int n, size_t len);
void	ft_bzero(void *str, size_t n);
void	*ft_calloc(size_t count, size_t size);

#endif
