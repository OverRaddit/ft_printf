/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 19:45:16 by gshim             #+#    #+#             */
/*   Updated: 2021/07/04 14:56:55 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	mypf_handle(va_list *ap, t_fd *info)
{
	long long	num;

	if (info->format == 'd' || info->format == 'i')
	{
		num = va_arg(*ap, int);
		if (num < 0)
		{
			info->sign = 0;
			num *= -1;
		}
		mypf_printd(num, info);
	}
	else if (info->format == 'c')
		mypf_printc(va_arg(*ap, int), info);
	else if (info->format == '%')
		mypf_printc('%', info);
	else if (info->format == 's')
		mypf_prints(va_arg(*ap, char *), info);
	else if (info->format == 'p')
		mypf_printp(va_arg(*ap, unsigned long long), info);
	else if (info->format == 'u' || info->format == 'x' || info->format == 'X')
		mypf_printd(va_arg(*ap, unsigned int), info);
}

void	fwp_parsing(char *field, int *i, t_fd *info, va_list *ap)
{
	while (is_flag(field[(*i)]))
	{
		info->flag = (info->flag == '-') ? '-' : field[(*i)];
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

void	getDigit(t_fd *info)
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
t_fd*		mypf_init(va_list *ap, char *field)
{
	t_fd	*info;
	int		i;

	info = (t_fd*)ft_calloc(1, sizeof(t_fd));
	info->sign = 1;
	i = 0;
	fwp_parsing(field, &i, info, ap);
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
	getDigit(info);
	return (info);
}

int ft_printf(const char *one,...)
{
	va_list	ap;
	t_fd	*info;
	int		i;
	int		fieldlen;
	int		ret;

	ret = 0;
	i = 0;
	va_start(ap, one);
	while (one[i] != '\0')
	{
		if (one[i] == '%')
		{
			fieldlen = 0;
			while (one[fieldlen + i + 1] != '\0' && !is_format(one[fieldlen + i + 1]))
				fieldlen++;
			info = mypf_init(&ap, ft_fielddup(one + i + 1, fieldlen));
			i += fieldlen + 2;
			mypf_handle(&ap, info);
			ret += info->ret;
			free(info);
			continue;
		}
		write(1, &one[i++], 1);
		ret += 1;
	}
	va_end(ap);
	return (ret);
}
