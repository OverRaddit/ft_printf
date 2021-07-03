/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_util3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 20:34:26 by gshim             #+#    #+#             */
/*   Updated: 2021/07/03 15:42:21 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned long long	recursive(unsigned long long n, int baselen)
{
	if (n == 0)
		return (0);
	return (1 + recursive(n / baselen, baselen));
}

char	*ft_uitoa(unsigned long long number, char *digit, int baselen)
{
	int			len;
	char		*ret;

	// %p면 0x에 해당하는 길이도 붙여줘야 한다.
	len = (number == 0) ? 1 : recursive(number, baselen);

	if (!(ret = malloc(sizeof(char) * (len + 1))))
		return (0);
	ret[len] = '\0';
	while (--len >= 0)
	{
		ret[len] = digit[number % baselen];
		number /= baselen;
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
