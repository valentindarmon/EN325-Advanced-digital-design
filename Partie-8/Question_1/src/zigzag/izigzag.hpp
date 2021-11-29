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
#ifndef _IZIGZAG_
#define _IZIGZAG_


#include <cstdio>
#include <cstdlib>
#include <cstdint>


const uint8_t _izz_[64] = {
        0,   1,  5,  6, 14, 15, 27, 28,
        2,   4,  7, 13, 16, 26, 29, 42,
        3,   8, 12, 17, 25, 30, 41, 43,
        9,  11, 18, 24, 31, 40, 44, 53,
        10, 19, 23, 32, 39, 45, 52, 54,
        20, 22, 33, 38, 46, 51, 55, 60,
        21, 34, 37, 47, 50, 56, 59, 61,
        35, 36, 48, 49, 57, 58, 62, 63
};


void izigzag(const int16_t din[64], int16_t dout[64])
{
    for(int32_t k = 0; k < 64; k += 1)
    {
        dout[k] = din[ _izz_[k] ];
    }
}


#endif