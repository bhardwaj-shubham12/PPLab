
	
	

#include <stdio.h>
#include <mpi.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

const int TAG = 1;

int isVowel(char c){
	switch(c){
		case 'a':
		
		case 'e':
		
		case 'i':
		
		case 'o':
		
		case 'u':
		
		case 'A':
		
		case 'E':
		
		case 'I':
		
		case 'O':
		
		case 'U': return 1;
		
		default: return 0;
	}
}

int nvc(char str[]){
	int v = 0;
	for(int i=0;i<strlen(str);i++)
		if(isalpha(str[i]))
			if(!isVowel(str[i]))
				v++;
	return v;
}

int main(int argc, char *argv[])
{
	int rank,size;
	int len;int len1;
	
	int A[10];int count = 0;
	char str[100];char str1[100];
	
	


	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Status status;

	if(rank == 0){
		printf("Enter string: ");
		fflush(stdout);
		gets(str);
		len = strlen(str);
	}

	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Bcast(&len,1,MPI_INT,0,MPI_COMM_WORLD);
	len1 = len/size;
	

	MPI_Scatter(str,len1,MPI_CHAR,str1,len1,MPI_CHAR,0,MPI_COMM_WORLD);
	str1[len1] = '\0';
	printf("Process %d:%s\n",rank,str1);

	count = nvc(str1);
	

	MPI_Gather(&count,1,MPI_INT,A,1,MPI_INT,0,MPI_COMM_WORLD);

	if(rank == 0) {
		int sum = 0;
		for(int i=0;i<size;i++){
			printf("Process %d found %d non vowels\n",i,A[i]);
			sum += A[i];
		}
		printf("Total non vowels %d\n",sum);
	}

	MPI_Finalize();
	return 0;
}