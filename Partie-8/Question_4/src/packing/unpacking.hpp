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

#ifndef _UNPACKING_
#define _UNPACKING_

#include <cstdio>
#include <cstdlib>
#include <cstdint>


void unpack(const int8_t din[192], int16_t dR[64], int16_t dG[64], int16_t dB[64])
{
#pragma HLS INLINE off
    uint32_t ptr = 0;
	for(int32_t y = 0; y < 64; y += 1)
	{
        dR[y] = din[ptr + 0];
        dG[y] = din[ptr + 1];
        dB[y] = din[ptr + 2];
        ptr  += 3;
	}
}

#endif
