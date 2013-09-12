/**
 * Class:         This class implements arbitrary precision integers and defines
 *                functions to operate on those.
 * Author:        Sheikh Mohammad Sajid
 * Creation Date: Thursday 20 October 2005
 */
#ifndef __BIGINTEGER_H_
#define __BIGINTEGER_H_

#include<iostream>
#include<climits>

namespace math {

const unsigned int MIN_SIZE = 1;

class BigInteger {
	protected:
		//char *hugeint; //buffer to hold the Big Integer
		unsigned int* hugeint; //buffer to hold the Big Integer
		int  size;     //maximum number of digits allowed
		int  digits;   //number of digits used in the array
		char sign;     //sign of the number, 0-positive,1-negative

	public:
		BigInteger();
		BigInteger(long int, int = MIN_SIZE);
		BigInteger(const char*, int = MIN_SIZE);
		~BigInteger();
		//Overloaded assignment functions
		BigInteger& operator =  (const char*);
		BigInteger& operator =  (BigInteger&);
		//Arithmetic functions
		BigInteger& operator +  (BigInteger&);
		BigInteger& operator += (BigInteger&);
		BigInteger& operator -  (BigInteger&);
		BigInteger& operator -= (BigInteger&);
		BigInteger& operator *  (BigInteger&);
		BigInteger& operator *= (BigInteger&);
		BigInteger& operator /  (BigInteger&) {return *this;} //TODO
		BigInteger& operator /= (BigInteger&) {return *this;} //TODO
		BigInteger& operator %  (BigInteger&) {return *this;} //TODO
		BigInteger& abs(BigInteger&) {return *this;} //TODO
		BigInteger& pow(BigInteger&) {return *this;} //TODO
		BigInteger& gcd(BigInteger&) {return *this;} //TODO
		//Logical functions
		bool        operator <  (BigInteger&) const;
		bool        operator <= (BigInteger&) const;
		bool        operator >  (BigInteger&) const;
		bool        operator >= (BigInteger&) const;
		bool        operator == (BigInteger&) const;
		bool        operator != (BigInteger&) const;
		//Bitwise functions
		BigInteger& operator ~ () {return *this;} //TODO
		BigInteger& operator & (BigInteger&) {return *this;} //TODO
		BigInteger& operator | (BigInteger&) {return *this;} //TODO
		//Shift Functions
		BigInteger& operator << (int) {return *this;} //TODO
		BigInteger& operator >> (int) {return *this;} //TODO
		//friend function to print out the big integer through cout object
		friend std::ostream& operator << (std::ostream&, const BigInteger&);
};

}
#endif
