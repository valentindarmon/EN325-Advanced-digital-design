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

#include "YUV2RGB.hpp"

//
// Usefull macro functions
//

void YUV2RGB(const int32_t din[192], int32_t dout[192])
{

}

void YUV2RGB(const int32_t din[192], uint8_t dout[192])
{
    int32_t conv[3];
    for(int32_t k = 0; k < 192; k += 3)
    {
        YUV2RGB(din + k, conv);

        for(int32_t i = 0; i < 3; i++)                 // Conversion des donnees de type int32_t
            dout[k+i] = conv[i] > 255 ? 255 : conv[i]; // en données de type uint8_t
    }
}
