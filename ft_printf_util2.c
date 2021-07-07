/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_util2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 20:32:55 by gshim             #+#    #+#             */
/*   Updated: 2021/07/07 17:24:06 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_atoi(const char *str, int *i)
{
	char		*s;
	long long	ret;
	int			sign;

	s = (char *)str;
	sign = 1;
	ret = 0;
	while ((9 <= s[*i] && s[*i] <= 13) || s[*i] == 32)
		(*i)++;
	if (s[*i] == '-' || s[*i] == '+')
		if (s[(*i)++] == '-')
			sign = -1;
	while (s[*i] != '\0' && (s[*i] >= '0' && s[*i] <= '9'))
	{
		ret = (ret * 10) + (s[*i] - '0');
		if (!(INT_MIN <= ret * sign && ret * sign <= INT_MAX))
			return (-1);
		(*i)++;
	}
	ret *= sign;
	return ((int)ret);
}

void	*ft_memset(void *ptr, int value, size_t num)
{
	unsigned int	i;
	unsigned char	*arr;

	arr = (unsigned char *)ptr;
	i = 0;
	while (i < num)
	{
		arr[i] = value;
		i++;
	}
	return (ptr);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*address;

	address = malloc(size * count);
	if (address == 0)
		return (0);
	return (ft_memset(address, 0, size * count));
}

char	*ft_strcat(char *dest, char *src)
{
	size_t	destlen;
	size_t	i;

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

char	*ft_strncat(char *dest, char *src, unsigned int nb)
{
	unsigned int	destlen;
	unsigned int	i;

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
