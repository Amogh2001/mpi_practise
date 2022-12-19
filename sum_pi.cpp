#include <iostream>
#include <cmath>
#include <iostream>
#include "mpi.h"


//Program to sum PI using Leibniz formula
//PI = 4*sum_n (-1**n/(2*n+1))
int main(int argc, char* argv[]) {
	int max_n = 1000;
	double sum = 0;
	MPI::Init(argc, argv);

	int num_procs = MPI::COMM_WORLD.Get_size();
	int rank = MPI::COMM_WORLD.Get_rank();

	for(int n = rank; n< max_n; n+=num_procs) 
	{
		double temp = 1.0/(2.0*((double)(n))+1.0);
		if(n%2 == 0)   //if n is even
		{
			sum += temp;
		}
		else 
		{
			//if n is odd
			sum -= temp;
		}

	}
	double global_sum;
	MPI::COMM_WORLD.Reduce(&sum, &global_sum, 1, MPI::DOUBLE, MPI::SUM, 0);
	if(rank == 0) {
		std::cout << "Pi is about " << 4.0*global_sum << " with error " << 4.0*global_sum-M_PI << "\n";
	}
	MPI::Finalize();
	return 0;
}

