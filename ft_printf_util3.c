/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_util3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 20:34:26 by gshim             #+#    #+#             */
/*   Updated: 2021/07/04 15:04:52 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned long long	recursive(unsigned long long n, int baselen)
{
	if (n == 0)
		return (0);
	return (1 + recursive(n / baselen, baselen));
}

char				*ft_uitoa(unsigned long long n, char *digit, int baselen)
{
	int			len;
	char		*ret;

	len = (n == 0) ? 1 : recursive(n, baselen);
	if (!(ret = malloc(sizeof(char) * (len + 1))))
		return (0);
	ret[len] = '\0';
	while (--len >= 0)
	{
		ret[len] = digit[n % baselen];
		n /= baselen;
	}
	return (ret);
}

char				*ft_strcat(char *dest, char *src)
{
	size_t destlen;
	size_t i;

	destlen = ft_strlen(dest);
	i = 0;
	while (src[i] != '\0')
	{
		dest[destlen + i] = src[i];
		i++;
	}
	dest[destlen + i] = '\0';
	return (dest);
}

char				*ft_strncat(char *dest, char *src, unsigned int nb)
{
	unsigned int destlen;
	unsigned int i;

	destlen = ft_strlen(dest);
	i = 0;
	while (src[i] != '\0')
	{
		if (i == nb)
		{
			break ;
		}
		dest[destlen + i] = src[i];
		i++;
	}
	dest[destlen + i] = '\0';
	return (dest);
}

char				*ft_fielddup(const char *src, int len)
{
	char	*str;

	while (src[len] != '\0' && !is_format(src[len]))
		len++;
	if (!(str = (char *)malloc(sizeof(char) * (len + 2))))
		return (0);
	str[len + 1] = '\0';
	while (len >= 0)
	{
		str[len] = src[len];
		len--;
	}
	return (str);
}

char				*ft_xtoa(unsigned long long number)
{
	int			len;
	char		*ret;
	char		*base;

	base = "0123456789abcdef";
	len = (number == 0) ? 1 + 2 : recursive(number, 16) + 2;
	if (!(ret = malloc(sizeof(char) * (len + 1))))
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
