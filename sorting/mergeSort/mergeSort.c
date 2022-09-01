void Merge(int A[], int L[], int R[], int L_len, int R_len)
{
	int i=0,j=0,k=0;
	
	while( i<L_len && j<R_len )
	{
		if( L[i] <= R[j] )
		{
			A[k] = L[i];
			i++;
		}
		else
		{
			A[k] = R[j];
			j++;
		}
		k++;
	}
	while( i<L_len)
	{
		A[k] = L[i];
		i++;k++;
	}
	while( j<R_len )
	{
		A[k] = R[j];
		j++;k++;
	}
}

void MergeSort(int A[],int size)
{
	if(size<2)return;
	int L_len = size/2;
	int R_len = size - L_len;
	
	int L[L_len],R[R_len];
	
	for(int i=0;i<L_len;i++)
	{
		L[i] = A[i];
	}
	for(int j=0;j<R_len;j++)
	{
		R[j] = A[j+L_len];
	}
	
	MergeSort(L,L_len);
	MergeSort(R,R_len);
	Merge(A,L,R,L_len,R_len);
}
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
32
33
34
35
36
37
38
39
40
41
42
43
44
45
46
47
48
49
50
51
void Merge(int A[], int L[], int R[], int L_len, int R_len)
{
	int i=0,j=0,k=0;
	
	while( i<L_len && j<R_len )
	{
		if( L[i] <= R[j] )
		{
			A[k] = L[i];
			i++;
		}
		else
		{
			A[k] = R[j];
			j++;
		}
		k++;
	}
	while( i<L_len)
	{
		A[k] = L[i];
		i++;k++;
	}
	while( j<R_len )
	{
		A[k] = R[j];
		j++;k++;
	}
}
 
void MergeSort(int A[],int size)
{
	if(size<2)return;
	int L_len = size/2;
	int R_len = size - L_len;
	
	int L[L_len],R[R_len];
	
	for(int i=0;i<L_len;i++)
	{
		L[i] = A[i];
	}
	for(int j=0;j<R_len;j++)
	{
		R[j] = A[j+L_len];
	}
	
	MergeSort(L,L_len);
	MergeSort(R,R_len);
	Merge(A,L,R,L_len,R_len);
}
