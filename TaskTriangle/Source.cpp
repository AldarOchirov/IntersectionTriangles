#include <iostream>
#include "OchirovA_intersection.h"

int main()
{
	double t1[9]{ 
		0, 0, 1, 
		0, 0, 2, 
		0, 1, 1 
	};

	double t2[9]{
		0, 0, 1, 
		0, 0, 2, 
		0, 1, -1
	};
	std::cout << OchirovA::hasIntersect(t1, t2) << std::endl;
	return 0;
}