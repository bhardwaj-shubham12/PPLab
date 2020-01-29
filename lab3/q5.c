#include<stdio.h>
#include<mpi.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
	/* code */
	MPI_Init(&argc,&argv);
	int oc=0,ec=0;
	int N;int r;
	int rank,size;int A[15],C[15];int c;int B[15];
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	if(!rank)
	{
		printf("Enter N:\n");scanf("%d",&N);
		printf("Enter array elements:\n");
		for(int i=0;i<N;i++)
		{
			scanf("%d",&A[i]);
		}
	}
	MPI_Bcast(&N,1,MPI_INT,0,MPI_COMM_WORLD);
	r=N/size;
	MPI_Scatter(A,r,MPI_INT,C,r,MPI_INT,0,MPI_COMM_WORLD);
	for(int i=0;i<r;i++)
	{
		if(C[i]%2==0)
		{
			C[i]=1;
		}
		else
		{
			C[i]=0;
		}
	}
	MPI_Gather(C,r,MPI_INT,B,r,MPI_INT,0,MPI_COMM_WORLD);

	if(!rank)
	{
		printf("Resulting array:\n");
		for(int i=0;i<N;i++)
		{
			printf("%d ",B[i]);
			if(!B[i])
			{
				oc++;
			}
			else
				ec++;
		}
		printf("\n");
		printf("Odd count:%d\n",oc);
		printf("Even count:%d\n",ec);

	}
	MPI_Finalize();

	return 0;
}