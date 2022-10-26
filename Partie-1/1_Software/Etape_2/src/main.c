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

int getRand(){
	return rand()%65535+1; //returns a rand int between 0 and 65535
}
int PGCD(int A, int B)
{
	if (A<1 || B<1) {
		return 0;
	}
	while(A!=B) {
		if (A>B) {
			A=A-B;
		} else {
			B=B-A;
		}
	}	
	return A;
}

int main (int argc, char * argv []){
	srand( time( NULL ) );
	printf("(II) Starting PGCD program\n");

	for(int i=0;i<10000;i++) {
		int a = getRand();
		int b = getRand();
		printf("PGCD de %d et %d donne %d\n",a,b,PGCD(a,b));
	}

	printf("(II) End of PGCD program\n");
  return 0;
}
