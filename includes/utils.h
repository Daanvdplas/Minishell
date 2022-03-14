/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-der <dvan-der@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/11 10:32:16 by rcappend      #+#    #+#                 */
/*   Updated: 2022/03/03 13:43:10 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <errno.h>
# include <stdio.h>

# define BUFFER_SIZE 10

char		*get_next_line(int fd);
int			check_line(char *line);
void		change_buffer(char *buffer, int buffer_size);
void		make_newline(char *new_line, char *line, \
			char *buffer, int buffer_size);
char		*add_buffer(char *line, char *buffer, \
			int buffer_size, int size_line);
int			check_buffer(char *buffer);

char		*ft_substr(char const *s, unsigned int start, size_t len);

char		*ft_strjoin(char const *s1, char const *s2);

char		*ft_strjoin_free(char *s1, char *s2);

char		*ft_strtrim(char const *s1, char const *set);

char		**ft_split(char const *s, char c);

char		*ft_itoa(int n);

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));

void		ft_putstr_fd(const char *s, int fd);

void		ft_putendl_fd(const char *s, int fd);

void		ft_putnbr_fd(int n, int fd);

int			ft_strncmp(const char *s1, const char *s2, size_t n);

char		*ft_strnstr(const char *haystack, const char \
			*needle, size_t len);

char		*ft_strchr(const char *s, int c);

char		*ft_strrchr(const char *s, int c);

size_t		ft_strlen(const char *str);

int			ft_isalnum(int c);

int			ft_isascii(int c);

int			ft_isalpha(int c);

int			ft_isdigit(int c);

int			ft_isprint(int c);

int			ft_tolower(int c);

int			ft_toupper(int c);

int			ft_isspace(int c);

void		ft_putchar_fd(char c, int fd);

void		ft_bzero(void *s, size_t n);

int			ft_atoi(const char *str);

void		*ft_memcpy(void *dst, void *src, size_t n);

void		*ft_memset(void *b, int c, size_t len);

void		*ft_memchr(const void *s, int c, size_t len);

void		*ft_memccpy(void *dst, const void *src, int c, size_t n);

void		*ft_memmove(void *dst, const void *src, size_t len);

int			ft_memcmp(const void *s1, const void *s2, size_t n);

void		*ft_calloc(size_t count, size_t size);

char		*ft_strdup(const char *s1);

int			ft_abs(int i);

int			ft_strcheck(char const *s, int (*f)(int));

size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);

void		ft_strcpy(char *dst, const char *src, size_t dstsize);

size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);

void		exit_error(const int code, const char *func, const char *msg);

void		ft_check_malloc(void *ptr, char *func);

void		*ft_free_char_array(char **array);

void		ft_putnbr_fd(int n, int fd);

char		*ft_filter_str(char const *str, char c);

#	endif
