#include "BigInteger.h"
using namespace math;

/* initialises BigInteger class to size 30*/
BigInteger::BigInteger()
{	
	digits = 0;
	sign = 0;
	size = MIN_SIZE;  //default size

	//hugeint = new char[size];
	hugeint = new unsigned int[size];
	if(!hugeint) throw "Memory Allocation Error!";

	for(int i = 0; i < size; ++i)
		hugeint[i] = 0;
}

/* converts long to BigInteger*/
BigInteger::BigInteger(long int num, int sz = MIN_SIZE)
{
	size = sz;
	digits = 0;
	if(num >= 0)
		sign = 0;
	else {
		num =- num; //make it +ve
		sign = 1;
	}
	//initialise
	//hugeint = new char[size];
	hugeint = new unsigned int[size];
	if(!hugeint) throw "Memory Allocation Error!";

	for(int i = 0; i < size; ++i)
		hugeint[i] = 0;
	
	//convert long to huge
	int i = size - 1;
	while(num > 0) {
		hugeint[i] = num % 10000000000UL;
		num /= 10000000000UL;
		--i;
		++digits;
	}
}

/* converts char* to BigInteger*/
BigInteger::BigInteger(const char* str, int sz = MIN_SIZE)
{
    if(!str) throw "Not a Number Exception";
    //TODO: also check for non-numeric characters and sign bit
    
	sign = 0;

	digits = -1;
	while(str[++digits]);//calculate no of digits

	//since an unsigned int can hold a max of 10 digits, the size reqd is
    //(digits / 10) + 1 
    //size is either equal to the calculated value or
	//sz whichever is greater
	size = (digits / 10) + 1;
	size = (sz > size)? sz : size;
	
	//hugeint = new char[size];
	hugeint = new unsigned int[size];
	if(!hugeint) throw "Memory Allocation Error!";

	for(int i = 0; i < size; ++i)
		hugeint[i] = 0;

    int i = digits - 1; //indexes str
	int j = size - 1; //indexes hugeint	
	/*while(i >= 0)
		hugeint[j--] = str[i--] - 48;*/
	unsigned int current = 0;
	while(true) {
        current = current * 10 + str[i++] - 48;
        if((current * 10 + str[i] - 48) > UINT_MAX) break;
    }
    hugeint[j--] = current;
}

BigInteger::~BigInteger()
{
	delete []hugeint;
}

BigInteger& BigInteger::operator = (const char *str)
{
	sign = 0;
	int i = 0;
	//while(str[++i]=='0');//go to the first non-zero digit
	//--i;//index goes one step more than the first non -zero digit, so decrease
	digits = 0;
	while(str[++i]) ++digits;//calculate no of digits
	if(digits < 30) size = 30;
	else size = digits;
	
	delete []hugeint;
	//hugeint = new char[size];
	hugeint = new unsigned int[size];
	if(!hugeint) throw "Memory Allocation Error!";

	for(int k = 0; k < size; ++k)
		hugeint[k] = 0;

	int j = size - 1;
	i -= 2;//i goes two positions ahead, so subtract
	while(i >= 0)
		hugeint[j--] = str[i--] - 48;

	return *this;
}

BigInteger& BigInteger::operator = (BigInteger& in)
{
	if(size != in.size){
		delete hugeint;
		//hugeint = new char[in.size];
		hugeint = new unsigned int[size];
		if(!hugeint) throw "Memory Allocation Error!";

		size = in.size;
	}
	digits = in.digits;
	sign = in.sign;
	
	for(int i = 0; i < size; ++i)
		hugeint[i] = in.hugeint[i];

	return *this;
}

BigInteger& BigInteger::operator + (BigInteger& in)
{
	int sz,  //size of temp
		d1,  //to access the current array
		d2,  //to access the 'in' array
		d3,  //to access the temp array
		sum,
		carry = 0;
	BigInteger *p1, *p2, *p3;
	//check which number has more digits and create temp accordingly
	if(*this >= in) {
		p1 = this;
		d1 = size - 1;
		p2 = &in;
		d2 = in.size - 1;
		sz = size + 1;
	}
	else {
		p1 = &in;
		d1 = in.size - 1;
		p2 = this;
		d2 = size - 1;
		sz = in.size + 1;
	}
	p3 = new BigInteger(0L, sz);
	if(!p3) throw "Memory Allocation Error!";

	d3 = sz - 1;
	
	while(d1 >= 0 && d2 >= 0) {
		//add the last digits and carry the sum to the next level
		sum = p1->hugeint[d1] + p2->hugeint[d2] + carry;
		
		p3->hugeint[d3] = sum % 10;
		carry = sum / 10;

		--d1;--d2;--d3;
		++(p3->digits);
	}

	while(d1 >= 0) {
		sum = p1->hugeint[d1] + carry;
		p3->hugeint[d3] = sum % 10;
		carry = sum / 10;
		--d1;--d3;
		++(p3->digits);
	}

	p3->sign = 0;

	return *p3;
}

BigInteger& BigInteger::operator += (BigInteger& in)
{
	return (*this = *this + in);
}

BigInteger& BigInteger::operator - (BigInteger &in)
{
	int sz,
		d1,    //to access the current array
		d2,    //to access the 'in' array
		d3,        //to access the temp array
		borrow=0,
		diff;         //difference
	
	BigInteger *p1, *p2, *p3;
	if(*this >= in) { //first num >=  2nd num
		p1 = this;
		d1 = size - 1;
		p2 = &in;
		d2 = in.size - 1;
		sz = size;
		p3 = new BigInteger(0L, sz);
		if(!p3) throw "Memory Allocation Error!";

		d3 = sz - 1;
		p3->sign = 0;
	}
	else {
		p1 = &in;
		d1 = in.size - 1;
		p2 = this;
		d2 = size - 1;
		sz = in.size;
		p3 = new BigInteger(0L, sz);
		if(!p3) throw "Memory Allocation Error!";

		d3 = sz - 1;
		p3->sign = 1;
	}

	//p3=p1-p2
	
	while(d1 >= 0 && d2 >= 0) {
		diff = p1->hugeint[d1] - borrow - p2->hugeint[d2];

		if(diff >= 0) {//no borrow
			p3->hugeint[d3] = diff;
			borrow = 0;
		}
		else {//there is a borrow
			p3->hugeint[d3] = p1->hugeint[d1] + 10 - borrow - p2->hugeint[d2];
			borrow = 1;
		}

		-d1;--d2;--d3;
		++(p3->digits);
	}
	//no of digits in p1 is more than p2
	while(d1 >= 0) {
		p3->hugeint[d3--] = p1->hugeint[d1--] - borrow;
		++(p3->digits);
		borrow = 0;
	}	
	
	return *p3;	
}

BigInteger& BigInteger::operator -= (BigInteger& in)
{
	return (*this = *this - in);
}

BigInteger& BigInteger::operator * (BigInteger &in)
{
	int sz,    //size of the target array
		d1,    //to access the current array
		d2,    //to access the 'in' array
		d3;    //to access the temp array

	BigInteger *p1, *p2, *p3;
	if(digits >= in.digits) { //digits in this num >=  2nd num
		p1 = this;
		p2 = &in;
	}
	else {
		p1 = &in;
		p2 = this;
	}

	sz = digits + in.digits + 1;
	p3 = new BigInteger(0L, sz);
	if(!p3) throw "Memory Allocation Error!";

	p3->size = sz;
	p3->sign = sign ^ in.sign;
	
	d1 = p1->size - 1;
	d2 = p2->size - 1;
	d3 = p3->size - 1;
	int i = 2;//determines the starting position in the target array 
	        //the next multiplied value will be stored
	int sum,carry = 0,subsum;
	
	while(d2 >= (p2->size - p2->digits)){//for each digit in the smaller number
		while(d1 >= (p1->size - p1->digits)){//multiply with each digit of the bigger number
			sum = p2->hugeint[d2] * p1->hugeint[d1] + carry;
			//cout<<"sum="<<sum;
			subsum = p3->hugeint[d3] + sum % 10;//add with result of previous step
			//cout<<" subsum="<<subsum;
			carry = sum / 10;//carry is here
			//if there is carry in the last subsum 
			p3->hugeint[d3] = subsum % 10;
			carry += subsum / 10;    //add to the carry
			
			//cin>>subsum;
			--d1;--d3;
		}
		p3->hugeint[d3] = carry;//last carry
		/*for(int k=0;k<p3->size;k++)
			cout<<(int)p3->hugeint[k]<<" ";
		cout<<"\n";*/
		d1 = p1->size - 1;
		--d2;
		d3 = p3->size - i;
		++i;
		carry = 0;
	}
	//calculate number of digits in final number
	int k = 0;
	while(k < p3->size && p3->hugeint[k] == 0) ++k;
	p3->digits = p3->size - k;
	
	return *p3;
}

BigInteger& BigInteger::operator *= (BigInteger& in)
{
	return (*this = *this * in);
}

bool BigInteger::operator < (BigInteger &in) const
{
	if(digits < in.digits) return true;
	
	if(digits == in.digits){
		for(int i = 0; i < digits; ++i)
			if(hugeint[i] < in.hugeint[i])
				return true;
	}
	return false;
}

bool BigInteger::operator <= (BigInteger &in) const
{
	return operator<(in) ? true : operator==(in);
}

bool BigInteger::operator > (BigInteger &in) const
{
	return operator<(in) ? false : (operator==(in) ? false : true);
}

bool BigInteger::operator >= (BigInteger &in) const
{
	return operator<(in) ? false : true;
}

bool BigInteger::operator == (BigInteger &in) const
{
	if(digits != in.digits) 
		return false;
	else
		for(int i = 0; i < digits; ++i)
			if(hugeint[i] != in.hugeint[i])
				return false;

	return true;
}

bool BigInteger::operator != (BigInteger &in) const
{
	return !operator==(in);
}

std::ostream& math::operator << (std::ostream& out, const BigInteger &in)
{
	int i=0;
	while(i < in.size && in.hugeint[i] == 0) ++i;

	if(i == in.size)//number 0
		return out<<0;
	
	if(in.sign == 1) out<<'-';

	for(; i < in.size; ++i)
		out<<"["<<i<<"]-"<<in.hugeint[i];

	return out;
}
