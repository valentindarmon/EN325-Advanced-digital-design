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
#ifndef _PACKING_
#define _PACKING_


#include <cstdio>
#include <cstdlib>
#include <cstdint>


#define MIN(a,b) ((a<b)?a:b)
#define MAX(a,b) ((a<b)?b:a)
#define LIMIT(a,b,c) MIN(MAX(a,b),c)


void pack(const int16_t dY[64], const int16_t dU[64], const int16_t dV[64], int8_t dout[192])
{
#pragma HLS INLINE off
    uint32_t ptr = 0;
    for(int32_t y = 0; y < 64; y += 1)
    {
        dout[ptr + 0] = LIMIT(dY[y],  -128, 127);
        dout[ptr + 1] = LIMIT(dU[y],  -128, 127);
        dout[ptr + 2] = LIMIT(dV[y],  -128, 127);
        ptr          += 3;
    }
}


void pack(const int16_t dY[64], const int16_t dU[64], const int16_t dV[64], int16_t dout[192])
{
#pragma HLS INLINE off
    uint32_t ptr = 0;
    for(int32_t y = 0; y < 64; y += 1)
    {
        dout[y +   0] = dY[y];
    }
    for(int32_t y = 0; y < 64; y += 1)
    {
        dout[y +  64] = dU[y];
    }
    for(int32_t y = 0; y < 64; y += 1)
    {
        dout[y + 128] = dV[y];
    }
}


#endif
