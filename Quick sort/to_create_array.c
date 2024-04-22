#include<omp.h>
#include<stdio.h>
#include<stdlib.h>
int main()
{
	double start,end;
	start=omp_get_wtime();
	for(int i=1;i<=50000;i++)
		printf("%d\n",rand()%1000+0);
	end=omp_get_wtime();
	//printf("\nexecution time:%f\n",end-start);
}	
