#include"calc.h"
#include"func.h"

int main()
{
	printf("PLUS ");
	printf("%d\n", plus(10, 10));
	if(checkNum(plus(10,10))) printf("EVEN\n");
	else printf("ODD\n");

	printf("MINUS ");
	printf("%d\n", minus(10, 5));
	if(checkNum(minus(10, 5))) printf("EVEN\n");
	else printf("ODD\n");
}
