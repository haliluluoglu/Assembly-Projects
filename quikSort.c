#include <stdio.h>
#define MAX 100

void quiksort(int[],int,int);
void swap(int*,int*);
void print(int*,int);

int main()
{
	int arr[MAX];
	int n,i;
	printf("Enter size of array: ");
	scanf("%d", &n);
	printf("Enter array: ");
	for(i=0; i<n; i++)
	{
		scanf("%d", &arr[i]);
	}
	printf("Regular array: \n");
	print(arr, n);
	quikSort(arr,0,MAX-1);
	printf("Sorted array: \n");
	print(arr, n);
	return 0;
}
void swap(int *num1, int *num2)
{
	int temp;
	temp=*num1;
	*num1=*num2;
	*num2=temp;
}
void quikSort(int arr[], int low , int high)
{
	int pivot,i,j;
	
	if(low<high)
	{
		pivot=low;
		i=low;
		j=high;
		while(i<j)
		{
			
			while((arr[i]<=arr[pivot])&&(i<high))
			{
				i++;
			}
			while(arr[j]>arr[pivot])
			{
				j--;
			}
			if(i<j)
			{
				swap(&arr[i],&arr[j]);
			}
		}
		swap(&arr[pivot], &arr[j]);
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
