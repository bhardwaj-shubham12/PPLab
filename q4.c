#include <stdio.h>
#include <mpi.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int merge(char str1[], char str2[], char result[]){
	int len = strlen(str1);
	int x = 0;
	for(int i=0;i<len;i++){
		result[x++] = str1[i];
		result[x++] = str2[i];
	}
	result[x] = '\0';
	return x;
}

int main(int argc, char *argv[])
{
	int rank,size;
	int len;
	int sublen;
	char result[100];char str1[100];char str2[100];
	char sub1[100];char sub2[100];
	int lenm=0;
	char buf[75];

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Status status;

	if(rank == 0){
		printf("String 1:");
		scanf("%s",str1);
		len = strlen(str1);
		printf("String 2:");
		fflush(stdout);
		scanf("%s",str2);
	}

	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Bcast(&len,1,MPI_INT,0,MPI_COMM_WORLD);
	sublen = len/size;
	

	MPI_Scatter(str1,sublen,MPI_CHAR,sub1,sublen,MPI_CHAR,0,MPI_COMM_WORLD);
	sub1[sublen]='\0';
	MPI_Scatter(str2,sublen,MPI_CHAR,sub2,sublen,MPI_CHAR,0,MPI_COMM_WORLD);
	sub2[sublen]='\0';
	printf("Process %d:%s\n",rank,sub1);
	printf("Process %d:%s\n",rank,sub2);

	lenm = merge(sub1,sub2,buf);
	
	printf("Process %d: %s\n",rank,buf);


	MPI_Gather(buf,2*sublen,MPI_CHAR,result,2*sublen,MPI_CHAR,0,MPI_COMM_WORLD);

	if(rank == 0) {
		printf("Result string = %s\n",result);
	}

	MPI_Finalize();
	return 0;
}