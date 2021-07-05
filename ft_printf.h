/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 20:15:39 by gshim             #+#    #+#             */
/*   Updated: 2021/07/05 20:55:37 by gshim            ###   ########.fr       */
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

typedef struct s_ps
{
	char	blank;
	int		len;
	int		bufsize;
} t_ps;

typedef unsigned long long ULL;

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
char	*ft_strcat(char *dest, char *src);
char	*ft_strncat(char *dest, char *src, unsigned int nb);

//3
ULL	recursive(ULL n, int baselen);
char	*ft_uitoa(ULL number, char *digit, int baselen);
char	*ft_fielddup(const char *src, int *len);
char	*ft_xtoa(ULL number);

//printf 메인
int		mypf_handle(va_list *ap, t_fd *info);
int		ft_printf(const char *one,...);

//parse
int		handle_Field(va_list *ap, const char *str, int *i, int *totalbyte);
t_fd*	get_Field(va_list *ap, const char *field);
void	get_Field_fwp(const char *field, int *i, t_fd *info, va_list *ap);
void	get_Field_digit(t_fd *info);
int		get_Fieldlen(const char *str);

//print_number
char	*printd_prec(t_fd *info, t_ps *ps, ULL n);
int	printd_width(t_fd *info, t_ps *ps, char *temp);
int		print_number(ULL value, t_fd *info);

//mypf
int		print_char(char c, t_fd *info);
int		print_str(char *str, t_fd *info);
int		print_address(ULL n, t_fd *info);

//condition
t_ps	*ps_init(t_fd *info, ULL n);
char	get_ps_blank(t_fd *info);
int		get_ps_bufsize(t_fd *info, int len);
#endif
