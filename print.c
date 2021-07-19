/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 14:14:54 by gshim             #+#    #+#             */
/*   Updated: 2021/07/19 16:01:42 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_char(char c, t_fd *info)
{
	char	*ret;
	int		bufsize;
	char	blank;

	blank = get_ps_blank(info);
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
	return (info->ret);
}

int	print_str(char *str, t_fd *info)
{
	char	*ret;
	int		bufsize;

	if (str == 0)
		str = "(null)";
	if (info->precbit == 1 && info->prec == 0 && info->format == 's')
		str = "";
	bufsize = get_ps_bufsize(info, ft_strlen(str));
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
		return (info->ret);
	}
	info->ret = write(1, str, bufsize);
	return (info->ret);
}

int	print_address(t_ULL n, t_fd *info)
{
	char	*ret;
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
	ret = ft_calloc(len + 1, sizeof(char));
	if (!ret)
		return (-1);
	temp = ft_xtoa(n);
	ft_strncat(ret, temp, len);
	print_str(ret, info);
	free(ret);
	free(temp);
	return (info->ret);
}
