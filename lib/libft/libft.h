/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:08:37 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/10/31 13:46:33 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <fcntl.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 800
# endif

int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
size_t				ft_strlen(const char *s);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_isspace(char c);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
int					ft_atoi(const char *str);
char				*ft_strdup(const char *s1);
void				*ft_calloc(size_t count, size_t size);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);

int					ft_printf(int fd, const char *format, ...);
int					ft_error_w(int print_count, int write_return);
int					ft_putchar_fd(char c, int fd);
int					ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
int					ft_putnbr_fd(int n, int fd);
int					ft_putptr_fd(unsigned long ptr, int fd);
int					ft_putnbr_fd_hex(unsigned long n, int fd, int uppercase);
int					ft_putnbr_fd_uns(unsigned int n, int fd);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_itoa(int n);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);

char				*get_next_line(int fd);
void				ft_free(void **ptr);
size_t				ft_strlenc(const char *s, char c);
void				ft_print_char_array(char **array);
void				ft_print_int_array(int **array);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_char_array_len(char **array);
char				*ft_skipws(char *line);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

char				*ft_strcpy(char *dest, const char *src);
char				*ft_strcat(char *dest, const char *src);
char				*ft_strjoin(char *s1, char *s2, char *delim, int mode);
int					ft_str_empty(char *str);
char				*ft_strncpy(char *dest, const char *src, size_t n);

void				ft_remove_extra_spaces(char *str);
void				ft_white_spaces_into_spaces(char *str);
int					ft_abs(int n);
int					ft_isquote(char c);
t_list				*ft_split_args(char *str, char *delim);
char				*ft_strtok(char *str, char *delim);
void				ft_del(void *content);
char				**ft_lst_to_array(t_list **lst);
int					ft_isdelim(char c);
char				*ft_strndup(char *str, int n);
char				*ft_remove_char(char *str, char c);

#endif
