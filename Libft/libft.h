/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 12:42:10 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/07/09 22:50:28 by tzinaliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <string.h>
# include <stddef.h>
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>
# include "ft_printf/ft_printf.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
//checks if c is printable
int		ft_isprint(int c);
//size_t	ft_strlen(const char *str);
void	*ft_memset(void *buffer, int c, size_t SIZE);
void	ft_bzero(void *b, size_t SIZE);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
int		ft_toupper(int c);
int		ft_tolower(int c);
// locates the first occurence of str
char	*ft_strchr(const char *str, int c);
// locates the last occurence of str
char	*ft_strrchr(const char *str, int c);
int		ft_strncmp(const char *str, const char *str0, size_t size);
int		ft_strcmp(char *s1, char *s2);

void	*ft_memchr(const void *str, int c, size_t n);
int		ft_memcmp(const void *str, const void *str0, size_t n);
// locate a string in a substring
char	*ft_strnstr(const char *big, const char *little, size_t len);
// ft_isspace is an atoi helper
int		ft_isspace(int c);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s);
//duplicate str but only up to n;
char	*ft_strndup(const char *s, size_t n);


//Part 2
char	*ft_substr(char const *str, unsigned int start, size_t len);
char	*ft_strjoin(char const *str, char const *str0);
char	*ft_strtrim(char const *str, char const *set);
// helper functions for ft_split
size_t	size_word(char const *str, char c);
size_t	count_words(const char *str, char c);

// splits str into array of strs and more specifically returns an memory 
// allocated array of memory allocated strings;
char	*ft_itoa(int n);
char	*ft_strmapi(char const *str, char (*f)(unsigned int, char));
void	ft_striteri(char *str, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *str, int fd);
void	ft_putendl_fd(char *str, int fd);
//put_int print_int
void	ft_putnbr_fd(int n, int fd);

//list handling
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new_);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new_);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/*gnl*/
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 7
# endif

// Use OPEN_MAX directly from limits.h
# define MAX_FDS OPEN_MAX

# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

void	cy(char *dest, const char *src);
size_t	ft_strcat(char *dest, const char *src, size_t size);
char	*ft_strjoin(char const *str, char const *str0);
char	*extract_line(char *buffer);
char	*trim_buffer(char *buffer);
char	*ft_strchr(const char *str, int c);

char	*get_next_line(int fd);

#endif
