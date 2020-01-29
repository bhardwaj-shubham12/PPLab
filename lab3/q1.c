#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int fact(int n)
{
	int f=1;
	for(int i=1;i<=n;i++)
	{
		f=f*i;
	}
	return f;
}

int main(int argc,char *argv[])
{
	int rank,size;int c;
	int A[10],B[10];int sum=0;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	if(!rank)
	{
		for(int i=0;i<size;i++)
		{
			A[i]=rand()%10+1;
		}
	}

	MPI_Scatter(A,1,MPI_INT,&c,1,MPI_INT,0,MPI_COMM_WORLD);
	printf("Received number %d in process %d\n",c,rank);
	c=fact(c);
	MPI_Gather(&c,1,MPI_INT,B,1,MPI_INT,0,MPI_COMM_WORLD);

	if(!rank)
	{
		printf("Received numbers in root\n");
		for(int i=0;i<size;i++)
		{
			printf("%d ",B[i]);
			sum+=B[i];
		}
		printf("Sum is :%d\n",sum);
	}
	MPI_Finalize();
	return 0;
}
