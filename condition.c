/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 16:40:23 by gshim             #+#    #+#             */
/*   Updated: 2021/07/04 20:40:20 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	get_Field_blank(t_fd *info)
{
	char	blank;

	blank = ' ';
	if (info->format == 'c' || info->format == 's' || info->format == 'p')
		blank = ' ';
	else if (info->flag == '0')
		blank = (info->flag == '0') ? '0' : ' ';
	return (blank);
}

int	get_Field_bufsize(t_fd *info, int len)
{
	int	bufsize;

	bufsize = (len < info->prec && info->prec > 0) ? info->prec : len;
	bufsize = (!info->sign) ? bufsize + 1 : bufsize;
	return (bufsize);
}

// void	print_width(t_fd *info,int bufsize, char blank, char *temp)
// {
// 	char	*buf;

// 	buf = (char*)ft_calloc(info->width, sizeof(char));
// 	if (blank == '0' && !info->sign)
// 		buf[0] = '-';
// 	if (info->flag != '-')
// 		ft_memset(buf + (buf[0] == '-'), blank, info->width - bufsize);
// 	ft_strncat(buf, temp, bufsize);
// 	if (info->flag == '-')
// 		ft_memset(buf + bufsize, blank, info->width - bufsize);
// 	write(1, buf, info->width);
// 	info->buf = info->width;
// 	free(buf);
// 	//free(temp);
// }
