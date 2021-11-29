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

#include <cstdio>
#include <cstdlib>
#include <cstdint>


#define MIN(a,b) ((a<b)?a:b)
#define MAX(a,b) ((a<b)?b:a)
#define LIMIT(a,b,c) MIN(MAX(a,b),c)


const int Wl = 6; // 5 EST LA VALEUR MINIMUM AFIN D'ASSURER LA QUALITE VISUELLE


const int32_t C1 = ((1<<Wl) * 0.299);
const int32_t C2 = ((1<<Wl) * 0.587);
const int32_t C3 = ((1<<Wl) * 0.114);
const int32_t C4 = ((1<<Wl) * 0.16874);
const int32_t C5 = ((1<<Wl) * 0.33126);
const int32_t C6 = ((1<<Wl) * 0.5);
const int32_t C7 = ((1<<Wl) * 0.41869);
const int32_t C8 = ((1<<Wl) * 0.08131);


void RGB2YUV(const uint8_t din[192], int8_t dout[192])
{
#pragma HLS INLINE off
	for(int32_t k = 0; k < 192; k += 3)
	{
        const int32_t R = din[k+0];
        const int32_t G = din[k+1];
        const int32_t B = din[k+2];

		const int32_t Y   = 0 + (int)C1 * R + (int)C2 * G + (int)C3 * B;
		const int32_t Cb  = 0 - (int)C4 * R - (int)C5 * G + (int)C6 * B;
		const int32_t Cr  = 0 + (int)C6 * R - (int)C7 * G - (int)C8 * B;

		const int32_t fY  =  (Y  >> (Wl)) - 128;
		const int32_t fCb =  (Cb >> (Wl));
		const int32_t fCr =  (Cr >> (Wl));

        dout[k+0]     = LIMIT(fY,  -128, 127);
        dout[k+1]     = LIMIT(fCb, -128, 127);
        dout[k+2]     = LIMIT(fCr, -128, 127);
	}
}


void RGB2YUV_full(const uint8_t din[192], int16_t dout[192])
{
#pragma HLS INLINE off
    for(int32_t k = 0; k < 192; k += 3)
    {
        const int32_t R = din[k+0];
        const int32_t G = din[k+1];
        const int32_t B = din[k+2];

        const int32_t Y   = 0 + (int)C1 * R + (int)C2 * G + (int)C3 * B;
        const int32_t Cb  = 0 - (int)C4 * R - (int)C5 * G + (int)C6 * B;
        const int32_t Cr  = 0 + (int)C6 * R - (int)C7 * G - (int)C8 * B;

        const int32_t fY  =  (Y  >> (Wl)) - 128;
        const int32_t fCb =  (Cb >> (Wl));
        const int32_t fCr =  (Cr >> (Wl));

        dout[  0 + k/3]     = LIMIT(fY,  -128, 127);
        dout[ 64 + k/3]     = LIMIT(fCb, -128, 127);
        dout[128 + k/3]     = LIMIT(fCr, -128, 127);
    }
}
