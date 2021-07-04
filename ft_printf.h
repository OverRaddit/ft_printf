/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 20:15:39 by gshim             #+#    #+#             */
/*   Updated: 2021/07/04 15:04:31 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
#define FT_PRINTF_H

# include <limits.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

typedef struct s_fd
{
	char	flag;
	int		width;
	int		prec;
	char	format;
	int		ret;
	int		precbit;
	int		sign;
	char	*digit;
	int		baselen;
} t_fd;

//1
int		is_format(char c);
int		is_flag(char c);
int		max(int x, int y);
int		min(int x, int y);
size_t	ft_strlen(const char *str);

//2
int		ft_atoi(const char *str, int *i);
void	*ft_memset(void *ptr, int value, size_t num);
void	*ft_calloc(size_t count, size_t size);

//3
unsigned long long	recursive(unsigned long long n, int baselen);
char	*ft_uitoa(unsigned long long number, char *digit, int baselen);
char	*ft_strcat(char *dest, char *src);
char	*ft_strncat(char *dest, char *src, unsigned int nb);
char	*ft_fielddup(const char *src, int len);
char	*ft_xtoa(unsigned long long number);

//printf
void	mypf_handle(va_list *ap, t_fd *info);
void	fwp_parsing(char *field, int *i, t_fd *info, va_list *ap);
void	getDigit(t_fd *info);
t_fd*	mypf_init(va_list *ap, char *field);
int		ft_printf(const char *one,...);

//mypf
void	mypf_printd(unsigned long long value, t_fd *info);
void	mypf_printc(char c, t_fd *info);
void	mypf_prints(char *str, t_fd *info);
void	mypf_printp(unsigned long long n, t_fd *info);

#endif
