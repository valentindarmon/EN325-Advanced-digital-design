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

inline int32_t min (int32_t a, int32_t b           ){ return ((a<b)?a:b); }
inline int32_t max (int32_t a, int32_t b           ){ return ((a>b)?a:b); }
inline int32_t clip(int32_t a, int32_t b, int32_t c){ return min(max(a,b),c); }

void YUV2RGB(const int32_t din[192], int32_t dout[192])
{
        const int32_t y = din[0];
        const int32_t u = din[1];
        const int32_t v = din[2];

        const int32_t r = y                       + 1.402   * (v - 128);
        const int32_t g = y - 0.34414 * (u - 128) - 0.71414 * (v - 128);
        const int32_t b = y + 1.772   * (u - 128);
    
        dout[0] = clip(r, 0, 255);
        dout[1] = clip(g, 0, 255);
        dout[2] = clip(b, 0, 255);
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
