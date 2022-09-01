#include <stdio.h>

void swap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}
 
int Partition(int A[], int start, int end)
{
	int pivot = A[end];
	int pIndex = start;
	
	for(int i=start; i<end; i++)
	{
		if( A[i] <= pivot )
		{
			swap(&A[i],&A[pIndex]);
			pIndex++;
		}
		for(int i = 0; i < 8; i++)
            printf("%d\t", A[i]);
        printf("\n");
	}
	swap(&A[end],&A[pIndex]);
	return pIndex;
}
 
void QuickSort(int A[], int start, int end)
{
	if(start<end)
	{
		int pIndex = Partition(A,start,end);
		printf("pIndex: %d\n", pIndex);
		QuickSort(A,start,pIndex-1);
		QuickSort(A,pIndex+1,end);
	}
}
