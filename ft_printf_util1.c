/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_util1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 20:30:41 by gshim             #+#    #+#             */
/*   Updated: 2021/06/29 20:32:15 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		is_format(char c)
{
	char *formats;

	formats = "cspdiuxX%";
	// 성능 개선을 위한 알파벳체크
	if (!(c >= 'a' && c <= 'z') && (c >= 'A' && c <= 'Z'))
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
	// .은 다른부분에서 파싱 가능하니 한번 빼봅시다.

	flags = "-0*";
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
