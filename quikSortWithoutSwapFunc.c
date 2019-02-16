#include <stdio.h>
#define MAX 6

void quiksort(int[],int,int);
void print(int*,int);

int main()
{
	int arr[MAX] = {1,5,0,3,2,6};
	printf("Regular array: \n");
	print(arr, MAX);
	quikSort(arr,0,MAX-1);
	printf("Sorted array: \n");
	print(arr, MAX);
	return 0;
}
void swap(int *num1, int *num2)
{
	int *temp;
	*temp=*num1;
	*num1=*num2;
	*num2=*temp;
}
void quikSort(int arr[], int low , int high)
{
	int pivot,i,j,temp;
	
	if(low<high)
	{
		pivot=low;
		i=low;
		j=high;
		while(i<j)
		{
			
			while(arr[i]<=arr[pivot])
			{
				i++;
			}
			while(arr[j]>arr[pivot])
			{
				j--;
			}
			if(i<j)
			{
				temp=arr[i];
				arr[i]=arr[j];
				arr[j]=temp;
			}
		}
		temp=arr[pivot];
		arr[pivot]=arr[j];
		arr[j]=temp;
		 
		quikSort(arr, low, j-1);
		quikSort(arr, j+1, high);
	}
}
void print(int *array, int n)
{
	int i;
	
	for(i=0; i<n; i++)
	{
		printf("%d\t", array[i]);
	}
	printf("\n");
}
