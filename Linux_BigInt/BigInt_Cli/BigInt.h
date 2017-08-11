#ifndef _BIGINT_H
#define _BIGINT_H

#include"SeqList.h"

class BigInt
{
public:
    BigInt(long x=0);
    BigInt(const BigInt &bt);
    BigInt& operator=(const BigInt &bt);
    ~BigInt();
public:
    void LoadData(u_long sz);
    void PrintData()const;
    void BigIntCopy(char *buf, size_t len, size_t &pos);
    void clear_head_zero();
public:
    void SetSymbol(Symbol sign);
    Symbol GetSymbol()const;
public:
    u_char back()const;
    void clear();
    u_long size()const;
    void push_back(u_char x);
    void pop_back();
    u_char& operator[](u_long i);
    const u_char& operator[](u_long i)const;
public:
    bool operator==(const BigInt &bt)const;
    bool operator!=(const BigInt &bt)const;
private:
    SeqList<u_char> big;
};

#endif
