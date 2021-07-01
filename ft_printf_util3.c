/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_util3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 20:34:26 by gshim             #+#    #+#             */
/*   Updated: 2021/06/29 20:50:09 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long	recursive(long long n)
{
	if (n == 0)
		return (0);
	return (1 + recursive(n / 10));
}

int			getbuf(long long n, char **ret)
{
	int		len;

	if (n < 0)
		//len = recursive(-1 * n) + 1;  부호때문에 고침
		len = recursive(-1 * n);
	else if (n == 0)
		len = 1;
	else
		len = recursive(n);
	if (!(*ret = (char*)malloc(sizeof(char) * (len + 1))))
		return (-1);
	(*ret)[len] = '\0';
	return (len);
}

char				*ft_itoa(int n)
{
	int			len;
	long long	number;
	char		*ret;

	number = (long long)n;
	len = getbuf(number, &ret);
	if (len == -1)
		return (0);
	if (n < 0)
		number *= -1;
	while (--len >= 0)
	{
		ret[len] = (int)(number % 10) + '0';
		number /= 10;
	}
	// if (n < 0)
	// 	ret[0] = '-';
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
