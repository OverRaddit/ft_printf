/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_util2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 20:32:55 by gshim             #+#    #+#             */
/*   Updated: 2021/07/03 21:43:55 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr(int n)
{
	int		i;
	char	buf[11];

	if (n < 0)
	{
		if (n == -2147483648)
		{
			write(1, "-2147483648", 11);
			return ;
		}
		write(1, "-", 1);
		n = n * -1;
	}
	i = -1;
	if (n == 0)
		write(1, "0", 1);
	while (n > 0)
	{
		buf[++i] = (n % 10 + 48);
		n = n / 10;
	}
	while (i >= 0)
	{
		write(1, &buf[i--], 1);
	}
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

// void	ft_putstr(char *s)
// {
// 	if (!s)
// 		return ;
// 	write(1, s, ft_strlen(s));
// }

int		ft_atoi(const char *str, int *i)
{
	char		*s;
	long long	ret;
	int			sign;

	s = (char *)str;
	ret = 0;
	while ((9 <= s[*i] && s[*i] <= 13) || s[*i] == 32)
		(*i)++;
	if (s[*i] == '-' || s[*i] == '+')
		sign = (s[(*i)++] == '-') ? -1 : 1;
	else
		sign = 1;
	while (s[*i] != '\0' && (s[*i] >= '0' && s[*i] <= '9'))
	{
		ret = (ret * 10) + (s[*i] - '0');
		if (!(INT_MIN <= ret * sign && ret * sign <= INT_MAX))
			return ((sign < 0) ? 0 : -1);
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
