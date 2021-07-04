/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 19:45:16 by gshim             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/07/04 23:58:50 by gshim            ###   ########.fr       */
=======
/*   Updated: 2021/07/04 21:42:33 by gshim            ###   ########.fr       */
>>>>>>> f2c05612212358a1dee2764f9afb8ce7d120f70e
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	mypf_handle(va_list *ap, t_fd *info)
{
	long long	num;
	int			ret;

	ret = 0;
	if (info->format == 'd' || info->format == 'i')
	{
		num = va_arg(*ap, int);
		if (num < 0)
		{
			info->sign = 0;
			num *= -1;
		}
		ret = print_number(num, info);
	}
	else if (info->format == 'c')
		ret = print_char(va_arg(*ap, int), info);
	else if (info->format == '%')
		ret = print_char('%', info);
	else if (info->format == 's')
		ret = print_str(va_arg(*ap, char *), info);
	else if (info->format == 'p')
		ret = print_address(va_arg(*ap, unsigned long long), info);
	else if (info->format == 'u' || info->format == 'x' || info->format == 'X')
		ret = print_number(va_arg(*ap, unsigned int), info);
	return (ret);
}

void	get_Field_fwp(const char *field, int *i, t_fd *info, va_list *ap)
{
	while (is_flag(field[(*i)]))
	{
		if (info->flag != '-')
			info->flag = field[(*i)];
		(*i)++;
	}
	if (field[(*i)] == '*')
	{
		info->width = va_arg(*ap, int);
		(*i)++;
	}
	else if (field[(*i)] >= '1' && field[(*i)] <= '9')
		info->width = ft_atoi(field, i);
	if (field[(*i)] == '.')
	{
		info->precbit = 1;
		(*i)++;
		if (field[(*i)] == '*')
		{
			info->prec = va_arg(*ap, int);
			(*i)++;
		}
		else
			info->prec = ft_atoi(field, i);
	}
}

void	get_Field_digit(t_fd *info)
{
	if (info->format == 'x')
		info->digit = "0123456789abcdef";
	else if (info->format == 'X')
		info->digit = "0123456789ABCDEF";
	else if (info->format == 'd' || info->format == 'i' || info->format == 'u')
		info->digit = "0123456789";
	if (info->digit != 0)
		info->baselen = ft_strlen(info->digit);
}

//%[플래그][폭][.정밀도][길이] 서식지정자
t_fd	*get_Field(va_list *ap, const char *field)
{
	t_fd	*info;
	int		i;

	info = (t_fd *)ft_calloc(1, sizeof(t_fd));
	info->sign = 1;
	i = 0;
	get_Field_fwp(field, &i, info, ap);
	if (is_format(field[i]))
		info->format = field[i];
	if (info->width < 0)
	{
		info->width *= -1;
		info->flag = '-';
	}
	if (info->prec < 0)
	{
		info->precbit = 0;
		info->prec = 0;
	}
	get_Field_digit(info);
	return (info);
}

// int	handle_Field(va_list ap, const char *str, int i)
// {
// 	fieldlen = 0;
// 	info = get_Field(&ap, ft_fielddup(str + i + 1, &fieldlen));
// 	i += fieldlen + 2;
// 	if (mypf_handle(&ap, info) == -1)
// 		return (-1);
// 	totalbyte += info->ret;
// 	free(info);
// 	continue ;
// }

int	get_Fieldlen(const char *str)
{
	int len;

	len = 0;
	while (str[len] != '\0' && !is_format(str[len]))
		len++;
	return (len);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	t_fd	*info;
	int		i;
	int		totalbyte;

	totalbyte = 0;
	i = 0;
	va_start(ap, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			info = get_Field(&ap, str + i + 1);
			i += get_Fieldlen(str + i + 1) + 2;
			if (mypf_handle(&ap, info) == -1)
				return (-1);
			totalbyte += info->ret;
			free(info);
			continue ;
		}
		write(1, &str[i++], 1);
		totalbyte += 1;
	}
	va_end(ap);
	return (totalbyte);
}
