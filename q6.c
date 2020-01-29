#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc,char *argv[])
{
	int rank,size;int M;
	int s;int arr[60];int arr2[60];
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_rank(MPI_COMM_WORLD,&size);
	if(!rank)
	{
		printf("Enter lenght of Array:\n");
		scanf("%d\n",&M);
		
		for(int i=0;i<M;i++)
		{
			scanf("%d",&arr[i]);
		}
	}
	MPI_Bcast(&M,1,MPI_INT,0,MPI_COMM_WORLD);
	int arr1[M];
	s=M/4;
	MPI_Scatter(arr,s,MPI_INT,arr1,s,MPI_INT,0,MPI_COMM_WORLD);
	for(int i=1;i<s;i++)
	{
		arr1[i]=arr1[i]+arr1[i-1];
	}
	printf("Rank %d The array is :\n",rank);
	for(int i=0;i<s;i++)
		printf("%d ",arr1[i]);
	printf("\n");
	MPI_Gather(arr1,s,MPI_INT,arr2,s,MPI_INT,0,MPI_COMM_WORLD);
	if(!rank)
	{
		printf("Final array\n");
		for(int i=0;i<M;i++)
		{
			printf("%d ",arr2[i]);
		}
		printf("\n");
	}
	MPI_Finalize();
	return 0;
	

	
}