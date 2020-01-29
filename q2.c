#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(int argc,char *argv[])
{
	int rank,size;float av;
	float A[10],c;int M;
	//int m;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	int arr[100];
	
	if(!rank)
	{
		
		printf("Enter M:\n");
		scanf("%d",&M);
		for(int i=0;i<size;i++)
		{
			for(int j=0;j<M;j++)
			{
				scanf("%d",&arr[j+(i*size)]);
			}
		}
	}
	
	MPI_Bcast(&M,1,MPI_INT,0,MPI_COMM_WORLD);
	//printf("%d ",m);
	int arr1[M];
	
	MPI_Scatter(arr,M,MPI_INT,arr1,M,MPI_INT,0,MPI_COMM_WORLD);
	
	printf("Values in process %d are\n",rank);
	for(int i=0;i<M;i++)
	{
		printf("%d ",arr1[i]);
		c=c+arr1[i];
	}
	printf("\n");
	c=c/M;
	MPI_Gather(&c,1,MPI_FLOAT,A,1,MPI_FLOAT,0,MPI_COMM_WORLD);

	if(!rank)
	{
		for(int i=0;i<size;i++)
		{
			av+=A[i];
		}
		av=av/size;
		printf("Average value:%f\n",av);
	}
	MPI_Finalize();
	return 0;
}