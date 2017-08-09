/*************************************************************************
    > File Name: calc.h
    > Author: Actually
    > Created Time: Fri 28 Jul 2017 11:12:06 AM CST
 ************************************************************************/

#ifndef CALC_H
#define CALC_H

#include "./BigInt/BigInt.h"

/*
char* bt2str(const BigInt &bt)
{
	char *str = (char *)malloc(bt.size() + 2);
	int j = 1;		

	for (int i=bt.size(); i > 0; --i)
		str[j++] = (int)bt[i]+48;

	if (bt.GetSymbol() == POSITIVE)
		str[0] = ' ';
	else
		str[0] = '-';

	str[j] = '\0';	
	return str;
}
*/

char* BigInt_calc(const char *btf, const char *bts, const char *op)
{
	u_long b1 = atol(btf);
	u_long b2 = atol(bts);

	BigInt bt1(b1), bt2(b2);
	BigInt bt;

	cout << bt1 << endl;
	cout << op << endl;
	cout << bt2 << endl;

	switch(*op)
	{
		case '+':
			BigInt::Add(bt, bt1, bt2);
			break;
		case '-':
			BigInt::Sub(bt, bt1, bt2);
			break;
		case '*':
			BigInt::Mul(bt, bt1, bt2);
		case '/':
			BigInt::Div(bt, bt1, bt2);
		case '%':
			BigInt::Mod(bt, bt1, bt2);
	}
	cout << "result:" << bt << endl;		
	
	return bt.toString();	
}



#endif  /*CALC_H*/

