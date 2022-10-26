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


int getRand(){
	return (rand()%65535)+1; //returns a rand int between 0 and 65535
}

void test(int a, int b) {
	assert(PGCD(a,b)==PGCD2(a,b)); 
}

int main (int argc, char * argv []){
	srand( time( NULL ) );
	printf("(II) Starting PGCD program\n");

	int tests = 100;
	printf("Testing for %d random values\n",tests);
	for(int i=0;i<tests;i++) {
		int a = getRand();
		int b = getRand();
		//printf("PGCD de %d et %d donne %d et %d\n",a,b,PGCD(a,b),PGCD2(a,b));
		test(a,b);
	}
	printf("Testing some specific values\n");
	
	test(1,1);
	test(1,9);
	test(129,87);
	test(87,129);
	test(65535,65535);
	test(65535,12654);
	test(45667,9871);

	printf("(II) End of PGCD program\n");
  return 0;
}
