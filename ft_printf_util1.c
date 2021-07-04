/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_util1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 20:30:41 by gshim             #+#    #+#             */
/*   Updated: 2021/07/04 01:34:17 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		is_format(char c)
{
	char *formats;

	formats = "cspdiuxX%";
	if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '%'))
		return (0);
	while (*formats)
	{
		if (c == *formats)
			return (1);
		formats++;
	}
	return (0);
}

int		is_flag(char c)
{
	char	*flags;

	flags = " -0";
	while (*flags)
	{
		if (c == *flags)
			return (1);
		flags++;
	}
	return (0);
}

size_t	ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int		max(int x, int y)
{
	return ((x > y) ? x : y);
}

int		min(int x, int y)
{
	return ((x < y) ? x : y);
}