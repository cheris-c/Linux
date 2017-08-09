/*************************************************************************
    > File Name: mystring.h
    > Author: Actually
    > Created Time: Fri 28 Jul 2017 03:03:28 PM CST
 ************************************************************************/

#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

int splitStr(char *str,const char *token, vector<string> &vecStr)
{
	char *s = NULL;

	for (s = strtok(str, token); s != NULL; s = strtok(NULL, token))
	{
		vecStr.push_back(s);
	}

	return vecStr.size();
}

#endif  /*MYSTRING_H*/
