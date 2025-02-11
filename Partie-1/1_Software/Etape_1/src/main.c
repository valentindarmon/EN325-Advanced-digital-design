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
	printf("(II) Starting PGCD program\n");

	printf("0 et 0 : %d \n", PGCD(0,0));
	printf("1 et 0 : %d \n", PGCD(0,0));
	printf("0 et 1 : %d \n", PGCD(0,0));
	printf("65535 et 65535 : %d \n", PGCD(65535,65535));
	printf("65535 et 15456 : %d \n", PGCD(65535,15456));
	printf("89 et 117 : %d \n", PGCD(117,89));
	printf("117 et 89 : %d \n", PGCD(89,117));
	printf("4096 et 128 : %d \n", PGCD(0,0));
	printf("-1 et 1 : %d \n", PGCD(-1,1));

	printf("(II) End of PGCD program\n");
  return 0;
}
