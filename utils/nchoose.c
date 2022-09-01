#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

uint32_t nchoosek(uint32_t N, uint32_t k)
{
	uint32_t result = 1;
	int i;
	int M = k;
	for(i = N; i > N-k; --i)
	{
		result *= i/(M--);
	}
	return result;
}


int main()
{
	int N = 4;
	int k = 2;
	int r = nchoosek(N, k);
	int j = pow(-1, 3);
	printf("Final %d\t %d", r, j);
}
