/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 17:57:39 by gshim             #+#    #+#             */
/*   Updated: 2021/07/09 12:21:16 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
	else if (info->format == 'o')
		info->digit = "01234567";
	else if (info->format == 'd' || info->format == 'i' || info->format == 'u')
		info->digit = "0123456789";
	if (info->digit != 0)
		info->baselen = ft_strlen(info->digit);
}

t_fd	*get_Field(va_list *ap, const char *field)
{
	t_fd	*info;
	int		i;

	info = (t_fd *)ft_calloc(1, sizeof(t_fd));
	if (info == 0)
		return (0);
	info->sign = 1;
	i = 0;
	get_Field_fwp(field, &i, info, ap);
	if (is_format(field[i]))
		info->format = field[i];
	if (get_Field_exception(info) == -1)
		return (0);
	get_Field_digit(info);
	return (info);
}

int	get_Field_exception(t_fd *info)
{
	if (info->width == INT_MIN)
	{
		free(info);
		return (-1);
	}
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
	return (0);
}

int	get_Fieldlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0' && !is_format(str[len]))
		len++;
	return (len);
}
