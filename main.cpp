#include<iostream>
#include<cstdio>
#include<alloc.h>
#include"BigInteger.h"

using namespace std;
using namespace math;
//using math::operator<<;

typedef enum {NONE=-1, PLUS='+', MINUS='-', MUL='*'} operator_t;

void calc(BigInteger &num1, BigInteger &num2, operator_t op)
{
	switch(op) {
		case PLUS:
			num1 = num1 + num2;
			break;
		case MINUS:
			num1 = num1 - num2;
			break;
		case MUL:
			num1 = num1 * num2;
			break;
		default:
			std::cout<<"Unrecognised operator!"<<op<<endl;
			break;
	}
}

int main()
{
	try{
		BigInteger hugeint1, hugeint2;
		int size = 30, i=0;
		char *str = new char[size];
		char ch;
		operator_t  op = NONE;
	
		while((ch = std::getchar()) != 'q'){
			if(ch >= '0' && ch <= '9'){//digits
				str[i++] = ch;
				if(i == size){
					realloc(str,size += 30);
					if(!str) throw "Memory Allocation Error!";
				}
				continue;
			}
			//control comes here means next character is non digit
			str[i] = 0;//terminate the string
			i = 0;
			switch(ch) {
				case '+':
				case '-':
				case '*':
					if(op == NONE){//first operand
						hugeint1 = str;
						op = (operator_t) ch;
					}	
					else{//second operand
						hugeint2 = str;
						calc(hugeint1, hugeint2, op);
						op = (operator_t) ch;
						//cout<<hugeint1<<"K"<<endl;
					}
					break;
				case '\n':
					if(op == NONE)//first operand
						hugeint1 = str;
					else{//second operand
						hugeint2 = str;
						calc(hugeint1, hugeint2,op);
						std::cout<<hugeint1<<endl;
					}
					op = NONE;
					break;
				case 'c'://clear memory
					op = NONE;
					break;
				default:
					std::cout<<"Not a number!\n";
					op = NONE;
					break;
			}
		}
	}
	catch(const char *err){
		std::cout<<err;
	}
}
