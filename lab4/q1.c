#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<ctype.h>

int main(int argc,char *argv[])
{
	int info=MPI_Init(&argc,&argv);

	MPI_Errhandler_set(MPI_COMM_WORLD,MPI_ERRORS_RETURN);

	int rank,size;

	if(info!=MPI_SUCCESS)
	{
		printf("Error occured\n");
		exit(1);
	}

	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	int info2=MPI_Comm_size(MPI_COMM_WORLD,&size);

	if(info2!=MPI_SUCCESS)
	{
		printf("Error occured\n");
		exit(1);
	}
	int fact=1;int factsum=0;
	for(int i=1;i<=rank;i++)
		fact=fact*i;
	printf("Process %d fact :%d\n",rank,fact);
	MPI_Scan(&fact,&factsum,1,MPI_INT,MPI_SUM,MPI_COMM_WORLD);

	if(rank==size-1)
	{
		printf("The sum is :%d\n",factsum);
	}
	MPI_Finalize();
	return 0;
}