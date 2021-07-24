/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 20:15:39 by gshim             #+#    #+#             */
/*   Updated: 2021/07/24 14:48:57 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

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
	char	signchar;
	char	*digit;
	int		baselen;
}	t_fd;

typedef struct s_ps
{
	char	blank;
	int		len;
	int		bufsize;
}	t_ps;

typedef unsigned long long	t_ULL;

int		is_format(char c);
int		is_flag(char c);
int		max(int x, int y);
int		min(int x, int y);
size_t	ft_strlen(const char *str);

int		ft_atoi(const char *str, int *i);
void	*ft_memset(void *ptr, int value, size_t num);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strcat(char *dest, char *src);
char	*ft_strncat(char *dest, char *src, unsigned int nb);

t_ULL	recursive(t_ULL n, int baselen);
char	*ft_uitoa(t_ULL number, char *digit, int baselen);
char	*ft_fielddup(const char *src, int *len);
char	*ft_xtoa(t_ULL number);

int		mypf_handle(va_list *ap, t_fd *info);
int		ft_printf(const char *one, ...);
int		handle_Field(va_list *ap, const char *str, int *i, int *totalbyte);

t_fd	*get_Field(va_list *ap, const char *field);
void	get_Field_fwp(const char *field, int *i, t_fd *info, va_list *ap);
void	get_Field_digit(t_fd *info);
int		get_Field_exception(t_fd *info);
int		get_Fieldlen(const char *str);

char	*printd_prec(t_fd *info, t_ps *ps, t_ULL n);
int		printd_width(t_fd *info, t_ps *ps, char *temp);
int		print_number(t_ULL value, t_fd *info);

int		print_char(char c, t_fd *info);
int		print_str(char *str, t_fd *info);
int		print_address(t_ULL n, t_fd *info);

char	get_ps_blank(t_fd *info);
int		get_ps_bufsize(t_fd *info, int len);
char	get_ps_signchar(t_fd *info);
t_ps	*ps_init(t_fd *info, t_ULL n);
#endif
