/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 19:45:16 by gshim             #+#    #+#             */
/*   Updated: 2021/07/03 22:19:35 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"


void	mypf_printd(unsigned long long value, t_fd *info)
{
	char	*temp;
	char	*ret;
	int		bufsize;
	int		i;
	int		j;
	int		len;
	char	blank;

	// prec이 존재하면 '0'플래그는 무시된다.
	info->flag = (info->flag == '0' && info->precbit == 1) ? ' ' : info->flag;
	blank = (info->prec == 0) && (info->flag == '0') ? '0' : ' ';

	len = (value == 0) ? 1 : recursive(value, info->baselen);
	// 최종버퍼 할당
	bufsize = max(max(len, info->prec), info->width);

	ret = (char*)ft_calloc(info->width, sizeof(char));

	// disp길이 설정(prec적용 후의 길이)
	bufsize = (len < info->prec && info->prec != 0) ? info->prec : len;
	bufsize = (!info->sign) ? bufsize + 1 : bufsize;
	temp = (char*)ft_calloc(bufsize + 1, sizeof(char));
	i = 0;
	j = 0;

	// 정밀도
	if (blank == ' ' && !info->sign)
		temp[i++] = '-';
	if (len < info->prec)
		while (j++ < info->prec - len)
			temp[i++] = '0';
	// value 넣기
	// itoa 함수에 주석을 넣었으니 나중에 잘 수정해둘것.
	// value가 0이면서 prec가 없으면 공백으로 출력한다.

	if (value == 0 && info->precbit == 1 && info->prec == 0)
		bufsize--;
	else
		ft_strcat(temp, ft_uitoa(value, info->digit, info->baselen));
	//printf("1.<%s>\n",ret);
	if (bufsize < info->width)
	{
		if (blank == '0' && !info->sign)
			ret[0] = '-';
		if (info->flag != '-')
			ft_memset(ret + (ret[0] == '-'), blank, info->width - bufsize);
		ft_strncat(ret, temp, bufsize);
		//printf("2.<%s>\n",ret);
		if (info->flag == '-')
			ft_memset(ret + bufsize, blank, info->width - bufsize);
		//printf("3.<%s>\n",ret);
		write(1, ret, info->width);
		info->ret = info->width;
		free(ret);
		free(temp);
		return ;
	}
	info->ret = bufsize;
	if (blank != ' ' && !info->sign)
		write(1, "-", 1);
	write(1, temp, ft_strlen(temp));
	free(temp);
}

void	mypf_printc(char c, t_fd *info)
{
	char	*ret;
	int		bufsize;
	int		len;
	int		i;
	char	blank;


	blank = (info->flag == '0' && info->format == '%') ? '0' : ' ';
	i = 0;
	len = 1;
	bufsize = (len > info->prec && info->prec > 0) ? info->prec : len;
	if (bufsize < info->width)
	{
		ret = (char*)ft_calloc(info->width, sizeof(char));
		if (info->flag != '-')
			ft_memset(ret, blank, info->width - bufsize);
		ft_strncat(ret, &c, bufsize);
		if (info->flag == '-')
			ft_memset(ret + bufsize, ' ', info->width - bufsize);
		info->ret = write(1, ret, info->width);
		free(ret);
		return ;
	}
	write(1, &c, bufsize);
	info->ret = bufsize;
}

void	mypf_prints(char *str, t_fd *info)
{
	char	*ret;
	int		bufsize;
	int		len;
	int		i;

	// .s, .0s 같이 나오면 출력하지 않는다.
	if (str == 0)
		str = "(null)";
	if (info->precbit == 1 && info->prec == 0 && info->format == 's')
		str = "";
	i = 0;
	len = ft_strlen(str);
	// 문제의 구간 len 값이 없을때(0) 예외처리를 해줘야 함. 0이상으로 바꿀까?
	bufsize = (len > info->prec && info->prec > 0) ? info->prec : len;
	//printf("bufsize: %d, width: %d\n",bufsize,info->width);
	if (bufsize < info->width)
	{
		ret = (char*)ft_calloc(info->width, sizeof(char));
		if (info->flag != '-')
			ft_memset(ret, ' ', info->width - bufsize);

		ft_strncat(ret, str, bufsize);

		if (info->flag == '-')
			ft_memset(ret + bufsize, ' ', info->width - bufsize);
		info->ret = write(1, ret, info->width);
		free(ret);
		return ;
	}
	write(1, str, bufsize);
	info->ret = bufsize;
}

char	*ft_xtoa(unsigned long long number)
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

void	mypf_printp(unsigned long long n, t_fd *info)
{
	char	*temp;
	int		len;

	// 0x에 해당하는 길이를 추가로 더해줘야 한다.
	len = (n == 0) ? 1 + 2 : recursive(n, 16) + 2;
	temp = ft_calloc(len + 1, sizeof(char));

	ft_strncat(temp, ft_xtoa(n), len);
	if (n == 0 && info->precbit == 1 && info->prec == 0 && info->format == 'p')
	{
		mypf_prints("0x", info);
		free(temp);
		return ;
	}
	mypf_prints(temp, info);
	free(temp);
}

void	mypf_handle(va_list *ap, t_fd *info)
{
	long long	num;

	if (info->format == 'd' || info->format == 'i')
	{
		num = va_arg(*ap, int);
		if (num < 0)
		{
			info->sign = 0;
			num *= -1;
		}
		mypf_printd(num, info);
	}
	else if (info->format == 'c')
		mypf_printc(va_arg(*ap, int), info);
	else if (info->format == '%')
		mypf_printc('%', info);
	else if (info->format == 's')
		mypf_prints(va_arg(*ap, char *), info);
	else if (info->format == 'p')
		mypf_printp(va_arg(*ap, unsigned long long), info);
	else if (info->format == 'u' || info->format == 'x' || info->format == 'X')
		mypf_printd(va_arg(*ap, unsigned int), info);
}

//%[플래그][폭][.정밀도][길이] 서식지정자
t_fd*		mypf_init(va_list *ap, char *field)
{
	t_fd	*info;
	int		i;

	info = (t_fd*)ft_calloc(1, sizeof(t_fd));
	// sign을 어디서 쓰는지 찾고 초기값을 1로 하는 이유 생각할것.
	info->sign = 1;
	i = 0;
	// flag parsing
	while (is_flag(field[i]))
	{
		info->flag = (info->flag == '-') ? '-' : field[i];
		i++;
	}

	// width parsing
	if (field[i] == '*')
	{
		info->width = va_arg(*ap, int);
		i++;
	}
	else if (field[i] >= '1' && field[i] <= '9')
		info->width = ft_atoi(field, &i);

	// prec parsing => .이 있으면 prec비트를 킨다.
	// prec비트가 켜지면 0플래그를 지운다.
	// 단, prec값이 음수이고 해당 값을 *로 받아왔다면 0플래그를 살려준다.
	if (field[i] == '.')
	{
		info->precbit = 1;
		i++;
		if (field[i] == '*')
		{
			info->prec = va_arg(*ap, int);
			i++;
		}
		else
			info->prec = ft_atoi(field, &i);
	}

	// 음수처리
	if (info->width < 0)
	{
		info->width *= -1;
		info->flag = '-';
	}
	if (info->prec < 0)
	{
		info->precbit = 0;
		info->prec = 0;
	}
	// format parsing
	if (is_format(field[i]))
		info->format = field[i];

	if (info->format == 'x')
		info->digit = "0123456789abcdef";
	else if (info->format == 'X')
		info->digit = "0123456789ABCDEF";
	else if (info->format == 'd' || info->format == 'i' || info->format == 'u')
		info->digit = "0123456789";
	if (info->digit != 0)
		info->baselen = ft_strlen(info->digit);

	return (info);
}

int ft_printf(const char *one,...)
{
	va_list	ap;
	t_fd	*info;
	int		i;
	int		fieldlen;
	int		ret;

	ret = 0;
	i = 0;
	va_start(ap, one);
	while (one[i] != '\0')
	{
		if (one[i] == '%')
		{
			fieldlen = 0;
			while (one[fieldlen + i + 1] != '\0' && !is_format(one[fieldlen + i + 1]))
				fieldlen++;
			info = mypf_init(&ap, ft_fielddup(one + i + 1, fieldlen));
			i += fieldlen + 2;
			mypf_handle(&ap, info);
			ret += info->ret;
			free(info);
			continue;
		}
		write(1, &one[i++], 1);
		ret += 1;
	}
	va_end(ap);
	return (ret);
}
