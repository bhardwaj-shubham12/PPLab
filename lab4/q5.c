#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<ctype.h>

int main(int argc,char *argv[])
{
	int info=MPI_Init(&argc,&argv);
	int mat[4][4];int arr[4];int buf[16];int arr1[4];
	int ele;int occurences=0;int sum=0;
	int buf1[16];

	MPI_Errhandler_set(MPI_COMM_WORLD,MPI_ERRORS_RETURN);

	int rank,size;

	if(info!=MPI_SUCCESS)
	{
		printf("Error occured\n");
		exit(1);
	}

	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	if(!rank)
	{
		printf("Enter elements\n");
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				scanf("%d",&mat[i][j]);
				buf[j+(i*size)]=mat[i][j];
			}
		}

	}
	MPI_Scatter(buf,4,MPI_INT,arr,4,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scan(arr,arr1,4,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
	MPI_Gather(arr1,4,MPI_INT,buf1,4,MPI_INT,0,MPI_COMM_WORLD);

	if(!rank)
	{
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				//buf1[j+(i*size)]=arr1[i];
				mat[i][j]=buf1[j+(i*size)];
			}
		}
		printf("The modified array is\n");
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				printf("%d ",mat[i][j]);
			}
			printf("\n");
		}


	}
	MPI_Finalize();
	return 0;


}