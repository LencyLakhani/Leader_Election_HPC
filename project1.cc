#include<mpi.h>
#include <iostream>
#include<cstdlib>

int main( int argc, char *argv[] ){

	//initialize rank, size and leader_number variable 
	int rank, size, leader_number;

	//start mpi
	MPI_Init( &argc, &argv );

	MPI_Comm_rank(MPI_COMM_WORLD, &rank); // get current processor rank

	MPI_Comm_size(MPI_COMM_WORLD, &size); // get total size of processor
	
	//if no of processor is less than 5 or greater than 20 then it give error message and return
	if(size < 5 || size > 20){
		MPI_Finalize();
		std::cout<<"Please enter no of processors between 5 and 20" << std::endl;
		return 0;
	}
	
	srand(time(0));

	//initialize array for store random numbers
	int random[size];

	//generate random number for all processors
	if(rank == 0) {
		for(int i=0; i<size; i++){
			random[i] = (rand() % (99 - 10 + 1)) + 10;
		}
	}

	//broadcast random number
	MPI_Bcast(&random, size, MPI_INT, 0, MPI_COMM_WORLD);

	int d = random[rank] * 10 + (random[rank] % 2);
	int number = d*100 + rank; // calculate random number in "NNDRR" format
	std::cout<< "Random number= " << number << " by rank " << rank <<std::endl;

	int A[2] = {0,0};

	//First communication to find 2 max value
	if (rank == 0) {

		A[0] = number, A[1] = 0;

		MPI_Send(A, 2, MPI_INT, rank+1, 0, MPI_COMM_WORLD);

		std::cout <<"Rank 0 sent the value= " << A[0] << " " << A[1] << " to rank 1."<< std::endl;


		MPI_Recv(&A, 2, MPI_INT, (rank-1)%size, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		std::cout << std::endl <<"Rank 0 received value= " << A[0] <<" " << A[1] << std::endl;
	
	}else {

		MPI_Recv(&A, 2, MPI_INT, (rank-1)%size, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		std::cout << "Rank" << rank << " has received the value= " << A[0] << " " <<A[1] << " from rank ";

		std::cout << (rank-1)%size << std::endl;
		
		//Adjust array value to maximum
		if(number > A[0]){
			A[1] = A[0];
			A[0] = number;
		
		}else if(number > A[1] && number < A[0] ){
			A[1] = number;
		}	


		MPI_Send(A, 2, MPI_INT, (rank+1)%size, 0, MPI_COMM_WORLD);

		std::cout << "Rank " << rank <<" sent the value= " << A[0] << " " << A[1] <<" to rank ";

		std::cout << (rank+1)%size <<std::endl;

	}

	//for second communication

	if (rank == 0) {

		leader_number = A[1];

		if(leader_number == number){
			std::cout<< std::endl << "Rank 0 is the leader with number= " << leader_number << std::endl;
		}

		MPI_Send(&leader_number, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD);

		MPI_Recv(&leader_number, 1, MPI_INT, (rank-1)%size, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

	}

	else {

		MPI_Recv(&leader_number, 1, MPI_INT, (rank-1)%size, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		if(leader_number == number){
			std::cout<< std::endl<< "Rank " << rank << " is the leader with number= " << leader_number<< std::endl;
		}

		MPI_Send(&leader_number, 1, MPI_INT, (rank+1)%size, 0, MPI_COMM_WORLD);

	}


	MPI_Finalize();

	return 0;

}





