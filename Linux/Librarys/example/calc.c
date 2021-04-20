/*********************************************
*	calc.c
********************************************/


#include<stdio.h>
#include"calc.h"

int plus(int a, int b)
{
	printf("--- plus(%d, %d) ", a, b);
	return a+b;
}

int minus(int a, int b)
{
	printf("--- minus(%d, %d) ", a, b);
	return a-b;
}
