/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_util3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 20:34:26 by gshim             #+#    #+#             */
/*   Updated: 2021/07/05 17:32:15 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ULL	recursive(ULL n, int baselen)
{
	if (n == 0)
		return (0);
	return (1 + recursive(n / baselen, baselen));
}

char	*ft_uitoa(ULL n, char *digit, int baselen)
{
	int			len;
	char		*ret;

	if (n == 0)
		len = 1;
	else
		len = recursive(n, baselen);
	ret = malloc(sizeof(char) * (len + 1));
	if (ret == 0)
		return (0);
	ret[len] = '\0';
	while (--len >= 0)
	{
		ret[len] = digit[n % baselen];
		n /= baselen;
	}
	return (ret);
}

char	*ft_fielddup(const char *src, int *len)
{
	char	*str;

	while (src[(*len)] != '\0' && !is_format(src[(*len)]))
		(*len)++;
	str = (char *)malloc(sizeof(char) * ((*len) + 2));
	if (!str)
		return (0);
	str[(*len) + 1] = '\0';
	while ((*len) >= 0)
	{
		str[(*len)] = src[(*len)];
		(*len)--;
	}
	return (str);
}

char	*ft_xtoa(ULL number)
{
	int		len;
	char	*ret;
	char	*base;

	base = "0123456789abcdef";
	if (number == 0)
		len = 3;
	else
		len = recursive(number, 16) + 2;
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (0);
	ret[0] = '\0';
	ret[len] = '\0';
	ft_strncat(ret, "0x", 2);
	while (--len >= 2)
	{
		ret[len] = base[number % 16];
		number /= 16;
	}
	return (ret);
}
