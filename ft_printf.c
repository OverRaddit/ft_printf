#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>

#include "ft_printf.h"

/*
typedef struct t_fd
{
	char	flag;
	// 출력하는 길이를 뜻한다. 음수면 왼쪽정렬, 양수면 오른쪽정렬이다
	int		width;
	int		prec;
	char	format;
	int		ret;
	int		precbit;
	int		zeroflag;
} t_fd;

int		is_format(char c)
{
	char *formats = "cspdiuxX%";

	// 성능 개선을 위한 알파벳체크
	if (!(c >= 'a' && c <= 'z') && (c >= 'A' && c <= 'Z'))
		return (0);
	while (*formats)
	{
		if (c == *formats)
			return (1);
		formats++;
	}
	return (0);
}

int		is_flag(char c)
{
	// .은 다른부분에서 파싱 가능하니 한번 빼봅시다.
	char *flags = "-0*";

	while (*flags)
	{
		if (c == *flags)
			return (1);
		flags++;
	}
	return (0);
}

size_t	ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

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

void	ft_putstr(char *s)
{
	if (!s)
		return ;
	write(1, s, ft_strlen(s));
}

#include <limits.h>
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

static long long	recursive(long long n)
{
	if (n == 0)
		return (0);
	return (1 + recursive(n / 10));
}

static int			getbuf(long long n, char **ret)
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

char	*ft_itoa(int n)
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

char	*ft_strcat(char *dest, char *src)
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

char	*ft_strncat(char *dest, char *src, unsigned int nb)
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

int		max(int x, int y)
{
	return ((x > y) ? x : y);
}

int		min(int x, int y)
{
	return ((x < y) ? x : y);
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
*/

//=====================================================================
void	mypf_printd(int value, t_fd *info)
{
	char	*temp;
	char	*ret;
	int		bufsize;
	int		i;
	int		j;
	int		len;
	char	blank;

	// prec이 존재하면 '0'플래그는 무시된다.
	blank = (info->prec == 0) && (info->flag == '0') ? '0' : ' ';

	len = (value == 0) ? 1 : (int)recursive(value);
	// 최종버퍼 할당
	bufsize = max(max(len, info->prec), info->width);

	// 이거 그냥 calloc 써버릴까
	ret = (char*)malloc(sizeof(char) * info->width);
	ret[0] = '\0';
	ret[info->width] = '\0';

	// disp길이 설정(prec적용 후의 길이)
	bufsize = (len < info->prec && info->prec != 0) ? info->prec + (value < 0) : len + (value < 0);
	temp = (char*)malloc(sizeof(char) * (bufsize + 1));

	i = 0;
	j = 0;

	// 정밀도
	// -는 맨 마지막에 수동으로 붙여야 겠따!
	if (blank == ' ' && value < 0)
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
		ft_strcat(temp, ft_itoa(value));
	if (bufsize < info->width)
	{
		if (blank == '0' && value < 0)
			ret[0] = '-';
		if (info->flag != '-')
			ft_memset(ret + (ret[0] == '-'), blank, info->width - bufsize);
		ft_strncat(ret, temp, bufsize);
		if (info->flag == '-')
			ft_memset(ret + bufsize, blank, info->width - bufsize);
		write(1, ret, info->width);
		info->ret = info->width;
		free(ret);
		free(temp);
		return ;
	}
	info->ret = bufsize;
	if (blank != ' ' && value < 0)
		write(1, "-", 1);
	ft_putstr(temp);
	free(temp);
}

void	mypf_printc(char c, t_fd *info)
{
	char	*ret;
	int		bufsize;
	int		len;
	int		i;


	i = 0;
	len = 1;
	// 문제의 구간 len 값이 없을때(0) 예외처리를 해줘야 함. 0이상으로 바꿀까?
	bufsize = (len > info->prec && info->prec > 0) ? info->prec : len;
	//printf("bufsize: %d, width: %d\n",bufsize,info->width);
	if (bufsize < info->width)
	{
		ret = (char*)malloc(sizeof(char) * info->width);
		ret[info->width] = '\0';

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

void	mypf_prints(char *str, t_fd *info)
{
	char	*ret;
	int		bufsize;
	int		len;
	int		i;

	// .s, .0s 같이 나오면 출력하지 않는다.
	if (info->precbit == 1 && info->prec == 0)
		str = "";
	if (str == 0)
		str = "(null)";
	i = 0;
	len = ft_strlen(str);
	// 문제의 구간 len 값이 없을때(0) 예외처리를 해줘야 함. 0이상으로 바꿀까?
	bufsize = (len > info->prec && info->prec > 0) ? info->prec : len;
	//printf("bufsize: %d, width: %d\n",bufsize,info->width);
	if (bufsize < info->width)
	{
		ret = (char*)malloc(sizeof(char) * info->width);
		ret[info->width] = '\0';

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

// cspdiuxX%
void	mypf_handle(va_list *ap, t_fd *info)
{
	if (info->format == 'd')
	{
		mypf_printd(va_arg(*ap, int), info);
	}
	else if (info->format == 'c')
	{
		char arr[2];
		arr[0] = va_arg(*ap, int);
		arr[1] = '\0';

		mypf_printc(arr, info);
	}
	else if (info->format == 's')
	{
		mypf_prints(va_arg(*ap, char *), info);
	}

}

//%[플래그][폭][.정밀도][길이] 서식지정자
t_fd*		mypf_init(va_list *ap, char *field)
{
	t_fd		*info;
	int		i;

	info = (t_fd*)malloc(sizeof(t_fd));

	// memset으로 info전체를 0값으로 하는 것도 괜찮을듯.
	info->flag = 0;
	info->width = 0;
	info->prec = 0;
	info->ret = 0;
	info->precbit = 0;
	i = 0;
	// flag parsing
	if (is_flag(field[i]))
		info->flag = field[i++];

	// width parsing
	if (field[i] == '*')
	{
		info->width = va_arg(*ap, int);
		i++;
	}
	else if (info->flag == '*')
		info->width = va_arg(*ap, int);

	else if ((field[i] >= '0' && field[i] <= '9') || field[i] == '-')
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
			// prec이 존재하므로 0플래그를 꺼준다.
			info->flag = (info->flag == '0' && info->prec >= 0) ? ' ' : info->flag;
			i++;
		}
		else
		{
			info->prec = ft_atoi(field, &i);
			info->flag = info->flag == '0' ? ' ' : info->flag;
		}
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

	//printf("flag: %c, width: %d, prec: %d\n",info->flag,info->width,info->prec);
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
	fieldlen = 0;
	va_start(ap, one);
	while (one[i] != '\0')
	{
		if (one[i] == '%')
		{
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

/*
int main(){
	char *s = "abc";
	int a,b,d = 0;

	//a = ft_printf("-->|%-3.*d|<--\n", 4, -135);
	//b =    printf("-->|%-3.*d|<--\n", 4, -135);
	a = ft_printf("-->|%-16.*s|<--\n", 1, s);	//-->|    |<--
	b =    printf("-->|%-16.*s|<--\n", 1, s);	//-->|0   |<--
	printf("a: %d, b: %d\n", a, b);

	ft_printf("-->|%-7.6s|<--\n", s);	//-->|    |<--
	   printf("-->|%-7.6s|<--\n\n", s);	//-->|0   |<--

	d = 198;
	// ft_printf("-->|%-4.4d|<--\n", d);		//-->|0198|<--
	// ft_printf("-->|%--1.4d|<--\n", d);		//-->|0198|<--

	//printf("a: %d, b: %d\n", a, b);

	// a = ft_printf("나의결과: |%.4s|end\n", s);
	// b = printf("실제결과: |%.4s|end\n", s);
	// printf("a: %d, b: %d\n", a, b);

	// a = ft_printf("나의결과: |%*.*s|end\n", 10, 9, s);
	// b = printf("실제결과: |%*.*s|end\n", 10, 9, s);
	// printf("a: %d, b: %d\n", a, b);
}
*/