#include <stdio.h>
#include "ft_printf.h"
#include "ft_printf.c"
#include "ft_printf_util1.c"
#include "ft_printf_util2.c"
#include "ft_printf_util3.c"
#include "print.c"
#include "print_get.c"
#include "print_number.c"
#include "parse.c"
#include <limits.h>
int main(){

	int		a = -4;
	int		i = 8;
	int		j = -12;
	int		l = 0;
	a = printf("%*d\n", INT_MIN, 1);
	i = ft_printf("%*d\n", INT_MIN, 1);
	printf("%d, %d\n", a, i);
	//	printf("%15.20p\n", &a);
	//	ft_printf("%15.20p\n", &a);
	//	printf("%15.0p\n", &a);
		// printf("%x\n", 4000000000);
		// ft_printf("%x\n", 4000000000);
		// printf("% 0+-8.5i\n", 34);
		// ft_printf("% 0+-8.5i\n", 34);
	//	   printf("%.*o\n", -3, 12345);
	//	ft_printf("%.*o\n", -3, 12345);
	while(1){}
}
