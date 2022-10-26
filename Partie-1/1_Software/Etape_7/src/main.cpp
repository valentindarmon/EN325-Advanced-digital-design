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

#define CATCH_CONFIG_MAIN
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "assert.h"

#include "pgcd.hpp"
#include "catch.hpp"

TEST_CASE("Test du PGCD") {
	SECTION( "Lorsque A>B"){
		REQUIRE( PGCD(65535,1) == 1 );
		REQUIRE( PGCD(13,17) == 1 );
		REQUIRE( PGCD(129,87) == 3);
		REQUIRE( PGCD(45235,2897) == 1);
	}
	SECTION(" Lorsque A<B"){
		REQUIRE( PGCD(87,129) == 3 );
		REQUIRE( PGCD(2876,45235) ==1 );
	}
	SECTION("Lorsque A=B") {
		REQUIRE( PGCD(1,1) == 1 );	
		REQUIRE( PGCD(65534,65534) == 65534 );
	}

}
