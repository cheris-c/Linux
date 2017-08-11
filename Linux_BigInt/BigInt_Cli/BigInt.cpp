#include"BigInt.h"
#include<stdlib.h>
#include<unistd.h>

void BigInt::SetSymbol(Symbol sign)
{
	big.SetSymbol(sign);
}
Symbol BigInt::GetSymbol()const
{
	return big.GetSymbol();
}

BigInt::BigInt(long value)
{
	SetSymbol(POSITIVE);
	if(value == 0)
	{
		push_back(0);
	}
	else
	{
		if(value < 0)
		{
			SetSymbol(NEGATIVE);
			value  = abs(value);
		}
		while(value > 0)
		{
			push_back(value % 10);
			value /= 10;
		}
	}
}
BigInt::BigInt(const BigInt &bt):big(bt.big)
{}
BigInt& BigInt::operator=(const BigInt &bt)
{
    if(this != &bt)
    {
        big = bt.big;
    }
    return *this;
}
BigInt::~BigInt()
{}
/////////////////////////////////////
void BigInt::LoadData(size_t sz)
{
	clear();
	srand(time(NULL));
	for(int i=0; i<sz; ++i)
	{
		big.push_back(rand()%10);
	}
	clear_head_zero();
}
void BigInt::PrintData()const
{
	for(int i=size(); i>=1; --i)
	{
		cout<<(int)big[i];
	}
	cout<<endl;
}
u_long BigInt::size()const
{return big.size();}
u_char BigInt::back()const
{return big.back();}
void BigInt::push_back(u_char x)
{big.push_back(x);}
void BigInt::pop_back()
{big.pop_back();}
u_char& BigInt::operator[](u_long i)
{return big[i];}
const u_char& BigInt::operator[](u_long i)const
{return big[i];}
void BigInt::clear()
{
    big.clear();
}
void BigInt::clear_head_zero()
{
    while(size()>0 && *this!=0 && (*this).back() == 0)
    {
        pop_back();
    }
}
void BigInt::BigIntCopy(char *buf, size_t len, size_t &pos)
{
    if(pos == 0)
    {
        memcpy(buf,big.base,1); //copy 0 index
        pos++;
    }
    memcpy(buf,big.base+pos, len);
}
//////////////////////////////////////////
bool BigInt::operator==(const BigInt &bt)const
{
	if(size() != bt.size())
		return false;
	size_t i = 1;
	while(i <= size())
	{
		if((*this)[i] != bt[i])
			return false;
		++i;
	}
	return true;

}
bool BigInt::operator!=(const BigInt &bt)const
{
	return !(*this == bt);
}


