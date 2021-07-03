/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_util4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 20:36:31 by gshim             #+#    #+#             */
/*   Updated: 2021/07/03 20:05:09 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t i;
	size_t srclen;

	if (!dest && !src)
		return (0);
	srclen = 0;
	while (src[srclen] != '\0')
		srclen++;
	i = 0;
	while (i + 1 < size && i < srclen)
	{
		dest[i] = src[i];
		i++;
	}
	if (size > 0)
		dest[i] = '\0';
	return (srclen);
}

char	*ft_fielddup(const char *src, int len)
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

char	*ft_strdup(const char *src)
{
	int		i;
	char	*str;

	i = 0;
	while (src[i] != '\0')
		i++;
	if (!(str = (char *)malloc(sizeof(char) * (i + 1))))
		return (0);
	i = 0;
	while (src[i])
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*address;

	if (!(address = malloc(size * count)))
		return (0);
	return (ft_memset(address, 0, size * count));
}
