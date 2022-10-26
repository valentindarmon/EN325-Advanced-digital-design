/*
 * EN325-Advanced-digital-design teaching lab.
 * 
 * Copyright (C) { 2021 }  { Bertrand LE GAL} { Bordeaux-INP }
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
*/

#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "assert.h"
#include "time.h"

#include "pgcd.h"
#include "string.h"

void test(int a, int b) {
	assert(PGCD(a,b)==PGCD2(a,b)); 
}



int main (int argc, char * argv []){

	printf("(II) Starting PGCD program\n");

	FILE *fA; FILE *fB; FILE *fRes;
	 
	fA = fopen("./data/ref_A.txt","r");
	fB = fopen("./data/ref_B.txt","r");
	fRes = fopen("./data/ref_C.txt","r");
	
	char bufA[10];char bufB[10];char bufRes[10];
	int c=0;int pb=0;
	
	while (fgets(bufA,10,fA) && fgets(bufB,10,fB) && fgets(bufRes,10,fRes) ) {
		c++;
		//printf("%d: ",++c);
		//printf(" %d %d %d ",atoi(bufA),atoi(bufB),atoi(bufRes));
		//if (c%100==0) {printf("Test %d\n",c); }
		if(PGCD(atoi(bufA),atoi(bufB)) != atoi(bufRes) ) {
			pb++; printf("problem at %d : %d %d %d\n",c,atoi(bufA),atoi(bufB),atoi(bufRes));
		}
	}	
	printf("Found %d issues out of %d values\n",pb,c);
	printf("(II) End of PGCD program\n");
  return 0;
}
