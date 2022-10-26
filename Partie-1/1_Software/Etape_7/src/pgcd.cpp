#include "pgcd.hpp"
#include <stdio.h>
#include <assert.h>

int PGCD(int A, int B)
{
	assert(A>0);
	assert(B>0);
	assert(B<655536);
	assert(A<655336);
	int firstA = A;

	while(A!=B) {
		if (A>B) {
			A=A-B;
		} else {
			B=B-A;
		}
	}
	
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
