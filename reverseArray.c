#include <stdio.h>
#define MAX 5

int main()
{
	int i,j,k,tmp,a,b;
	int matrix[]={};
	for(i=0; i<MAX;i++)
	{
		for(j=i; j<MAX; j++)
		{
			a=(MAX*i)+j;
			b=(MAX*j)+i;
			tmp=matrix[a];
			matrix[a]=matrix[b];
			matrix[b]=tmp;
		}
	}
	for(i=0; i<MAX; i++)
	{
		k=MAX-1;
		for(j=0; j<k; j++)
		{
			a=(MAX*j)+i; 
			b=(MAX*k)+i;
			tmp=matrix[a];
			matrix[a]=matrix[b];
			matrix[b]=tmp;
			k--;
		}
	}
	for(i=0; i<1024; i++)
	{
		if(i%32==0)
		{
			printf("\n");
		}
		printf("%d\t", matrix[i]);
	}
	return 0;
}

