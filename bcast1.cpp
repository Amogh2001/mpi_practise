#include <iostream>
#include <cstdlib>
#include "mpi.h"

//program to throw dice using random numbers between 1-6 using MPI and broaddcast the result.

int main(int argc, char* argv[]) { 
	MPI::Init();
	int dice[3] = {0, 0, 0};
	//Process 0 sets the dice
	if(MPI::COMM_WORLD.Get_rank() == 0) {
		for(int i =0; i<3; i++) {
			dice[i] = (rand()%6) +1;
		}
	}
	//Now it broadcasts

	MPI::COMM_WORLD.Bcast(dice, 3, MPI::INT, 0);
	//Adding all results to dice[0]
	dice[0] += MPI::COMM_WORLD.Get_rank();
	//Reduce function to get maximumm
	int max;
	MPI::COMM_WORLD.Reduce(dice, &max, 1, MPI::INT, MPI::MAX, 0);
	MPI::Finalize();
}



