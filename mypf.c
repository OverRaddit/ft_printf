/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mypf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 14:14:54 by gshim             #+#    #+#             */
/*   Updated: 2021/07/05 20:54:43 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_char(char c, t_fd *info)
{
	char	*ret;
	int		bufsize;
	char	blank;

	blank = get_pf_blank(info);
	bufsize = 1;
	if (bufsize < info->width)
	{
		ret = (char *)ft_calloc(info->width, sizeof(char));
		if (!ret)
			return (-1);
		if (info->flag != '-')
			ft_memset(ret, blank, info->width - bufsize);
		ft_strncat(ret, &c, bufsize);
		if (info->flag == '-')
			ft_memset(ret + bufsize, ' ', info->width - bufsize);
		info->ret = write(1, ret, info->width);
		free(ret);
		return (0);
	}
	info->ret = write(1, &c, bufsize);
	return (0);
}

int	print_str(char *str, t_fd *info)
{
	char	*ret;
	int		bufsize;

	if (str == 0)
		str = "(null)";
	if (info->precbit == 1 && info->prec == 0 && info->format == 's')
		str = "";
	bufsize = get_pf_bufsize(info, ft_strlen(str));
	if (bufsize < info->width)
	{
		ret = (char *)ft_calloc(info->width, sizeof(char));
		if (!ret)
			return (-1);
		if (info->flag != '-')
			ft_memset(ret, ' ', info->width - bufsize);
		ft_strncat(ret, str, bufsize);
		if (info->flag == '-')
			ft_memset(ret + bufsize, ' ', info->width - bufsize);
		info->ret = write(1, ret, info->width);
		free(ret);
		return (0);
	}
	info->ret = write(1, str, bufsize);
	return (0);
}

int	print_address(ULL n, t_fd *info)
{
	char	*temp;
	int		len;

	if (n == 0 && info->precbit == 1 && info->prec == 0)
	{
		print_str("0x", info);
		return (0);
	}
	if (n == 0)
		len = 1 + 2;
	else
		len = recursive(n, 16) + 2;
	temp = ft_calloc(len + 1, sizeof(char));
	if (!temp)
		return (-1);
	ft_strncat(temp, ft_xtoa(n), len);
	print_str(temp, info);
	free(temp);
	return (0);
}
