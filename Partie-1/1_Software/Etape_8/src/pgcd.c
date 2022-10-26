#include "pgcd.h"
#include <stdio.h>
#include <assert.h>

int PGCD(int A, int B)
{
	int firstA=A;
	int firstB=B;
	
	assert(A>0);
	assert(B>0);
	assert(B<655536);
	assert(A<655365);

	while(A!=B) {
		if (A>B) {
			A=A-B;
		} else {
			B=B-A;
		}
	}

	assert(firstA>=A);
	assert(firstB>=B);
	assert(A>=1);
	assert(firstA%A==0);
	assert(firstA%B==0);
	return A;
}

int PGCD2(int N1, int N2) {
	if (N1<1 || N2<1) {
		return 0;
	}
	int a1=N1;
	int a2=N2;
	int temp;
	while(a2>0) {
		temp = a1;
		a1 = a2;
		a2 = temp%a2;
	}
	return a1;
}
