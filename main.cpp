#include <iostream>
#include "Matrix.h"

int main(void)
{
	Matrix a(7, 2), b(2, 2), c, d;

	a.fill("a.mtx");
	b.fill("b.mtx");

	a.print();
	b.print();

	try {
		//c = c + d;	//throws exception

		c = a + b;
		c.print();

		c = a * b;
		c.print();
	}
	catch (const char* msg)
	{
		std::cout << msg;
	}

	return 0;
}
