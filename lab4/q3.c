#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<ctype.h>

int main(int argc,char *argv[])
{
	int info=MPI_Init(&argc,&argv);
	int mat[3][3];int arr[3];int buf[9];
	int ele;int occurences=0;int sum=0;

	MPI_Errhandler_set(MPI_COMM_WORLD,MPI_ERRORS_RETURN);

	int rank,size;

	if(info!=MPI_SUCCESS)
	{
		printf("Error occured\n");
		exit(1);
	}


	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	int info2=MPI_Comm_size(MPI_COMM_WORLD,&size);

	if(!rank)
	{
		printf("Enter elements\n");
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)
			{
				scanf("%d",&mat[i][j]);
				buf[j+(i*size)]=mat[i][j];
			}
		}
		printf("\n");
		printf("Enter element to be searched:");scanf("%d",&ele);
	}
	MPI_Scatter(buf,3,MPI_INT,arr,3,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Bcast(&ele,1,MPI_INT,0,MPI_COMM_WORLD);
	for(int i=0;i<3;i++)
	{
		if(arr[i]==ele)
		{
			occurences++;
		}
	}
	printf("Ocuurences in %d is %d\n",rank,occurences);
	int info3=MPI_Scan(&occurences,&sum,1,MPI_INT,MPI_SUM,MPI_COMM_WORLD);

	if(info3!=MPI_SUCCESS)
	{
		printf("Error occured\n");
		exit(1);
	}

	if(rank==size-1)
	{
		printf("Number of occurences:%d\n",sum);
	}


}