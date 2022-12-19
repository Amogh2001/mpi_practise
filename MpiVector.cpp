#include <iostream>
#include "mpi.h"
#include "MpiVector.hpp"

//This program creates an array of all 1s

int main(int argc, char* argv[]) {
	MPI::Init(argc, argv);
	MpiVector all_ones(9);
	std::cout << "Local has [ " <<  all_ones.GetLo() << ", " << all_ones.GetHi() << ")\n";
	for(int i=all_ones.GetLo(); i<all_ones.GetHi(); i++) {
		all_ones[i] = 10;
	}
	assert(fabs(all_ones.CalculateNorm() - 3.0) < 1.0e-6);
	all_ones.UpdateGlobal();
	MPI::Finalize();
	return 0;
}

