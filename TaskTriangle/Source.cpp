#include <iostream>
#include "OchirovA_intersection.h"

int main()
{
	double t1[9]{ 
		3, 0, 0,
		0, 3, 0,
		0, 3, 0
	};

	double t2[9]{
		1.5, 1.4, 0,
		1.5, 1.4, 0,
		0, 0, 3
	};
	std::cout << OchirovA::hasIntersect(t1, t2) << std::endl;
	return 0;
}