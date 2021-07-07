/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 19:45:16 by gshim             #+#    #+#             */
/*   Updated: 2021/07/07 17:22:27 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	mypf_handle(va_list *ap, t_fd *info)
{
	long long	num;

	if (info->format == 'd' || info->format == 'i' || info->format == 'o')
	{
		num = va_arg(*ap, int);
		if (num < 0)
		{
			info->sign = 0;
			num *= -1;
		}
		return (print_number(num, info));
	}
	else if (info->format == 'c')
		return (print_char(va_arg(*ap, int), info));
	else if (info->format == '%')
		return (print_char('%', info));
	else if (info->format == 's')
		return (print_str(va_arg(*ap, char *), info));
	else if (info->format == 'p')
		return (print_address(va_arg(*ap, t_ULL), info));
	else if (info->format == 'u' || info->format == 'x' || info->format == 'X')
		return (print_number(va_arg(*ap, unsigned int), info));
	return (-1);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		i;
	int		totalbyte;

	totalbyte = 0;
	i = 0;
	va_start(ap, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			if (handle_Field(&ap, str, &i, &totalbyte) == -1)
				return (-1);
			continue ;
		}
		write(1, &str[i++], 1);
		totalbyte += 1;
	}
	va_end(ap);
	return (totalbyte);
}
