/*
 * Copyright 2020 Xilinx, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "RGB2YUV.hpp"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <paths.h>
#include <termios.h>
#include <sysexits.h>
#include <sys/param.h>
#include <sys/select.h>
#include <sys/time.h>
#include <time.h>
#include <cassert>
#include <iostream>

using namespace std;


static int fileDescriptor = -1;


void RGB2YUV(const uint8_t din[3], uint8_t dout[3])
{
    if( fileDescriptor == -1 )
    {
        printf("(II) Ouverture du port serie ttyUSB1 !\n");
        fileDescriptor = open("/dev/ttyUSB1", O_RDWR | O_NOCTTY );
        if(fileDescriptor == -1)
        {
            printf("(WW) Ouverture impossible du port ttyUSB1 !\n");
            printf("(II) Ouverture du port serie ttyUSB0 !\n");
            fileDescriptor = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY );
            if(fileDescriptor == -1)
            {
            printf("(WW) Ouverture impossible du port ttyUSB0 !\n");
                exit( EXIT_FAILURE );
            }
        }

        struct termios t;
        tcgetattr(fileDescriptor, &t); // recupère les attributs
        cfmakeraw(&t); // Reset les attributs
        t.c_cflag     = CREAD | CLOCAL;     // turn on READ
        t.c_cflag    |= CS8;
        t.c_cc[VMIN]  = 0;
        t.c_cc[VTIME] = 255;     // 5 sec timeout

        cfsetispeed(&t, B921600);
        cfsetospeed(&t, B921600);
        tcsetattr(fileDescriptor, TCSAFLUSH, &t); // envoie le tout au driver    
    }

	int wBytes = write( fileDescriptor, din, 192);
	if( wBytes != 192 )
    {
        printf("(EE) Erreur a l'emission des données (%d != %d)\n", wBytes, 192);
        exit( EXIT_FAILURE );
    }

    int rBytes = read( fileDescriptor, dout, 192);
    if( rBytes != 192 )
    {
        printf("(EE) Erreur a la reception des données (%d != %d)\n", rBytes, 192);
        exit( EXIT_FAILURE );
    }
}
