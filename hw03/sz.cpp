//
// g++ sz.cpp -o sz
// gcc sz.cpp -o sz -lstdc++
// what is the output of printf?
//
//#include <stdio.h>
#include <iostream>
using namespace std;

class ZeroByte {
	unsigned long long Arr[0];
};

class OneByte {
};

int main(void)
{
	ZeroByte zero;
	OneByte one;

	// error: 'printf' was not declared in this scope
	// with <stdio.h>
	// warning: format ‘%d’ expects argument of type ‘int’, 
	// but argument 2 has type ‘long unsigned int’ [-Wformat=]
	// output: sizeof zero: 0 one: 1
	// printf("sizeof zero: %d one: %d\n", sizeof(zero), sizeof(one));

	cout << "sizeof zero: " << sizeof(zero) << " one: " << sizeof(one) << "\n";

	return 0;
}
