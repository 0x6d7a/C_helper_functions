#include <stdio.h>

void swap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}
 
int Partition(int A[], int start, int end)
{
    int pivot = (rand() % (end - start + 1)) + start;
    int pIndex = start;

    swap(&A[end], &A[pivot]);

	for(int i=start; i<end; i++)
	{
		if( A[i] < A[end] )
		{
			swap(&A[i],&A[pIndex]);
			pIndex++;
		}
	}
    
	swap(&A[end],&A[pIndex]);
	return pIndex;
}
 
void select(int A[], int start, int end, int k)
{
	if(start<end)
	{
		int pIndex = Partition(A,start,end);
        if (pIndex > k)
        {
            return select(A, start, pIndex-1,k);
        }
        else if (pIndex < k)
        {
            return select(A, pIndex + 1, start, k);
        }

        return A[k];
        
	}
}
