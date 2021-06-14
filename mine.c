#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>

typedef struct fd
{
	char	flag;
	// 출력하는 길이를 뜻한다. 음수면 왼쪽정렬, 양수면 오른쪽정렬이다
	int		width;
	int		prec;
	char	format;

} fd;

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
		len = recursive(-1 * n) + 1;
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
	if (n < 0)
		ret[0] = '-';
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

int		my_max(int x, int y)
{
	return ((x > y) ? x : y);
}

void	mypf_printd(int value, fd *info)
{
	char	*temp;
	int		bufsize;
	int		i;
	int		j;
	char	blank;
	int		vlen;

	// value 출력시 길이가 몇인지를 알아낸다.
	vlen = (int)recursive(value);

	// bufsize = vlen, width, prec중 Max값을 가진다.
	bufsize = info->width == 0 ? vlen : info->width;
	bufsize = bufsize < info->prec ? info->prec : bufsize;

	temp = (char*)malloc(sizeof(char) * (bufsize + 1));
	temp[bufsize] = '\0';

	blank = ' ';
	// 아 이거 이해가안됨;;;
	// if (info->flag == '0') //mypf("나의결과: |%07.5d|end\n", 123);여기서 터짐;
	// 	blank = '0';
	i = 0;
	j = -1;
	/*
		기본적으로 width에 해당하는 크기의 버퍼가 제공된다.
		width의 나머지 부분은 ' '으로 채워진다.
		플래그가 '0'이라면 나머지 부분을 ' '이 아닌 '0'으로 채운다.
		단, prec값이 존재한다면 나머지 부분을 ' '로 둔다.
	*/

// 폭 규칙
	// vlen < width < prec인 경우 어떻게 되지?
	if (bufsize == info->width)
		// 빼는 값은 prec > vlen ? prec : vlen 이다....
		while (++j < bufsize - my_max(vlen, info->prec))
			temp[i++] = blank;
// 정밀도 규칙
	// 자릿수가 출력할 값보다 작을 경우, 정밀도 옵션을 무시한다.
	j = -1;
	if (vlen < info->prec)
	{
		blank = '0';
		while (++j < info->prec - vlen)
			temp[i++] = blank;
	}
// value 넣기
	ft_strcat(temp, ft_itoa(value));


	ft_putstr(temp);
	free(temp);
}

// cspdiuxX%
void mypf_handle(va_list *ap, fd *info)
{
	if (info->format == 'd')
	{
		mypf_printd(va_arg(*ap, int), info);
	}
	else if (info->format == 'c')
	{
		ft_putchar(va_arg(*ap, int));
	}
	else if (info->format == 's')
	{
		ft_putstr(va_arg(*ap, char *));
	}

}
//%[플래그][폭][.정밀도][길이] 서식지정자
fd* mypf_init(char *field)
{
	fd		*info;
	int		i;

	info = (fd*)malloc(sizeof(fd));
	info->flag = '@';
	info->width = 0;
	info->prec = 0;

	i = 0;
	// flag parsing
	if (is_flag(field[i]))
		info->flag = field[i++];
	// width parsing
	if (field[i] >= '0' && field[i] <= '9')
		info->width = ft_atoi(field, &i);
	// prec parsing
	if (field[i] == '.')
	{
		// 정밀도에 음수가 할당되면 무시한다는데 해당 로직을 추가해야할까..?
		i++;
		info->prec = ft_atoi(field, &i);
		if (info->prec < 0)
		{
			// 이것이 *로 넘겼을때는 적용이 안되는데,,,, 어휴
			info->width = 0;
			info->prec = 0;
		}
	}
	// format parsing
	if (is_format(field[i]))
		info->format = field[i];
	return (info);
}

int mypf(char *one,...)
{
	va_list	ap;
	int		i;
	int		fieldlen;
	char	*field;

	i = 0;
	fieldlen = 0;
	va_start(ap, one);
	while (one[i] != '\0')
	{
		if (one[i] == '%')
		{
			while (one[fieldlen + i + 1] != '\0' && !is_format(one[fieldlen + i + 1]))
				fieldlen++;
			field = ft_fielddup(one + i + 1, fieldlen);
			fd *info = mypf_init(field);
			//printf("flag: %c, width: %d, format: %c, prec: %d\n",info->flag,info->width,info->format,info->prec);
			i += fieldlen + 1;
			mypf_handle(&ap, info);
			free(info);
		}
		else
			write(1, &one[i], 1);
		i++;
	}
	va_end(ap);
	return (1);
}

int main(){
	//precision only
	// 음수, *, 플래그0
	mypf("나의결과: |%07.5d|end\n", 123);
	printf("실제결과: |%07.5d|end\n", 123);

	mypf("나의결과: |%*.*d|end\n", 7, -2, 123);
	printf("실제결과: |%*.*d|end\n", 7, -2, 123);

	// mypf("나의결과: |%05d|\n", 123);
	// printf("실제결과: |%05d|\n", 123);

	//mypf("hello %d name %s",123, "hello");
	// 사용한 결과 : |[asdf]|end\n
}

/*
	flag = '0' && prec값존재 => width가 무시됨?

	prec => 출력할 대상의 길이를 정함
	width => 출력할 버퍼의 길이를 정함
*/