#include <stdio.h>
// 가변인자 헤더로 추정됨.
#include <stdarg.h>

// , ...을 통해 가변인자로 받을 것임을 알려줌.
// 여기서 args는 가변인자의 개수를 의미함.
void printNumbers(int args, ...)
{
	// 가변인자의 시작! 메모리 주소를 저장하는 포인터.
	va_list ap;
	va_list ap2;

	// 가변 인자를 가져올 수 있도록 포인터를 설정한다.
	va_start(ap, args);
	va_copy(ap2, ap);
	for (int i=0; i < args; i++)
	{
		// int 크기만큼 가변인자 목록포인터에서 값을 가져옴.
		// 문자열로 예를들면 읽을 글자의 수만큼 str이 전진하는 느낌...!!
		int num = va_arg(ap, int);
		printf("[%d, ", num);
		printf("%d]", va_arg(ap2, int));
	}
	// 가변인자 처리가 끝났을 때 포인터를 NULL로 초기화 한다.
	va_end(ap);

	printf("\n");
}

// 첫 인자로 오는건 가변인자의 개수 아니었나??????
// types는 각 인자들의 자료형을 알파벳으로 적어놓은 string임
void printValues(char *types,...)
{
	va_list ap;
	int i = 0;

	va_start(ap, types);	// types라는 배열의 크기가 가변인자의 개수가 되나봄!
	while (types[i] != '\0')
	{
		switch (types[i])
		{
		case 'i':
			printf("%d ", va_arg(ap, int));
			break;
		case 'd':
			printf("%f ", va_arg(ap, double));
			break;
		case 'c':
			//?????????
			printf("%c ", va_arg(ap, int));
			break;
		case 's':
			printf("%s ", va_arg(ap, char *));
			break;
		default:
			break;
		}
		i++;
	}
	va_end(ap);

	printf("\n");
}


int main(){
	//printNumbers(5,6,7,8,9,10);
	printf("내 나이는 %d살이고 이름은 %s야.\n",25,"심건우");
	// types[0] = i, types[1] = s가 되는건가?
	printValues("i", 10);                                 // 정수
    printValues("ci", 'a', 10);                          // 문자, 정수
    printValues("dci", 1.234567, 'a', 10);               // 실수, 문자, 정수
    printValues("sicd", "Hello, world", 10, 'a', 1.23);  // 문자열, 정수, 문자, 실수

	// my test case
	printf("Hello World!");
	printf("small quote: \', big quote: \" \n");
	printf("Hello World!");
	printf("Hello World!");


    return 0;
}




/*
void va_copy(va_list dest, va_list src);

var_type을 설정할 때 char, short 의 경우에는 int로 대신 쓰고, flaot의 경우에는 double로 대신 쓴 이후 형 변환을 해주어야 한다.ex) char ch = (char) va_arg(ap, int);

va_arg() 함수는 현재 인수를 리턴한다. va_copy(), va_end(), va_start() 함수는 값을 리턴하지 않는다

공부자료 	https://www.notion.so/488f9dddb1cf4122aa588f89aa819dc9
*/