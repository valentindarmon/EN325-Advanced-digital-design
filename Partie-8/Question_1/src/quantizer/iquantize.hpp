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
#ifndef _IQUANTIZER_
#define _IQUANTIZER_

#include <cstdio>
#include <cstdlib>
#include <cstdint>

static const unsigned char iq_YTable[64]  = {
        3,   2,   2,   3,   5,   8,  10,  12,
        2,   2,   3,   4,   5,  12,  12,  11,
        3,   3,   3,   5,   8,  11,  14,  11,
        3,   3,   4,   6,  10,  17,  16,  12,
        4,   4,   7,  11,  14,  22,  21,  15,
        5,   7,  11,  13,  16,  21,  23,  18,
       10,  13,  16,  17,  21,  24,  24,  20,
       14,  18,  19,  20,  22,  20,  21,  20
};

// q = 90%
static const unsigned char iq_UVTable[64] = {
        3,   4,   5,   9,  20,  20,  20,  20,
        4,   4,   5,  13,  20,  20,  20,  20,
        5,   5,  11,  20,  20,  20,  20,  20,
        9,  13,  20,  20,  20,  20,  20,  20,
       20,  20,  20,  20,  20,  20,  20,  20,
       20,  20,  20,  20,  20,  20,  20,  20,
       20,  20,  20,  20,  20,  20,  20,  20,
       20,  20,  20,  20,  20,  20,  20,  20
};


void i_quantize_yuv(const int16_t din[192], int16_t dout[192])
{
#pragma HLS INLINE off
    for(int32_t y = 0; y < 64; y += 1)
    {
        dout[y] = din[y] * iq_YTable[y];
    }

    for(int32_t y = 0; y < 64; y += 1)
    {
        dout[y + 64] = din[y + 64] * iq_UVTable[y];
    }

    for(int y = 0; y < 64; y += 1)
    {
        dout[y + 128] = din[y + 128] * iq_UVTable[y];
    }
}


void i_quantize_y(const int16_t din[64], int16_t dout[64])
{
#pragma HLS INLINE off
    for(int32_t y = 0; y < 64; y += 1)
    {
        dout[y] = din[y] * iq_YTable[y];
    }
}


void i_quantize_uv(const int16_t din[64], int16_t dout[64])
{
#pragma HLS INLINE off
    for(int32_t y = 0; y < 64; y += 1)
    {
        dout[y] = din[y] * iq_UVTable[y];
    }
}


#endif