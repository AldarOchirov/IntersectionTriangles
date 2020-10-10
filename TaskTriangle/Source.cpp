#include <iostream>
#include "OchirovA_intersection.h"

int main()
{
	double t1[9]{ 
		1, 1.5, 0.1, 
		1, 1.5, 0.1, 
		1, 1.5, 0.1 
	};

	double t2[9]{
		1, 1, 0, 
		1, 1, 0, 
		1, 1, 1
	};
	std::cout << OchirovA::hasIntersect(t1, t2) << std::endl;
	return 0;
}