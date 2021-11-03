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
#include <cmath>

#define MIN(a,b) ((a<b)?a:b)
#define MAX(a,b) ((a<b)?b:a)
#define LIMIT(a,b,c) MIN(MAX(a,b),c)
//inline int32_t min (int32_t a, int32_t b           ){ return ((a<b)?a:b); }
//inline int32_t max (int32_t a, int32_t b           ){ return ((a>b)?a:b); }
//inline int32_t clip(int32_t a, int32_t b, int32_t c){ return min(max(a,b),c); }

const int32_t Wl = 5; // 5 EST LA VALEUR MINIMUM AFIN D'ASSURER LA QUALITE VISUELLE

const int32_t C1 = std::round((1<<Wl) * 0.299);
const int32_t C2 = std::round((1<<Wl) * 0.587);
const int32_t C3 = std::round((1<<Wl) * 0.114);
const int32_t C4 = std::round((1<<Wl) * 0.16874);
const int32_t C5 = std::round((1<<Wl) * 0.33126);
const int32_t C6 = std::round((1<<Wl) * 0.5);
const int32_t C7 = std::round((1<<Wl) * 0.41869);
const int32_t C8 = std::round((1<<Wl) * 0.08131);

void RGB2YUV(const int32_t din[3], int32_t dout[3])
{
    const int32_t R = din[0];
    const int32_t G = din[1];
    const int32_t B = din[2];

	const int32_t Y   = 0 + (int32_t)C1 * R + (int32_t)C2 * G + (int32_t)C3 * B;
	const int32_t Cb  = 0 - (int32_t)C4 * R - (int32_t)C5 * G + (int32_t)C6 * B;
	const int32_t Cr  = 0 + (int32_t)C6 * R - (int32_t)C7 * G - (int32_t)C8 * B;

	const int32_t fY  =  (Y  >> (Wl));
	const int32_t fCb =  (Cb >> (Wl)) + 128;
	const int32_t fCr =  (Cr >> (Wl)) + 128;

	dout[0]  = LIMIT(fY,  0, 255);
	dout[1]  = LIMIT(fCb, 0, 255);
	dout[2]  = LIMIT(fCr, 0, 255);
}

void RGB2YUV(const uint8_t din[192], int32_t dout[192])
{
    int32_t conv[3];
    for(int32_t k = 0; k < 192; k += 3)
    {
        for(int i = 0; i < 3; i++)  // Conversion des donnees de type uint8_t
            conv[i] = din[k+i];     // en données de type int32_t

        RGB2YUV(conv, dout + k);
    }
}
