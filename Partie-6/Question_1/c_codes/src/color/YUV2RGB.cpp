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

#include "YUV2RGB.hpp"

//
// Usefull macro functions
//
inline int32_t min (int32_t a, int32_t b           ){ return ((a<b)?a:b); }
inline int32_t max (int32_t a, int32_t b           ){ return ((a>b)?a:b); }
inline int32_t clip(int32_t a, int32_t b, int32_t c){ return min(max(a,b),c); }

void YUV_2_RGB(const uint8_t din[3], uint8_t dout[3])
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

void YUV2RGB(const uint8_t din[3], uint8_t dout[3])
{
        for(int i = 0; i < 192; i += 3)
                YUV_2_RGB(din + i, dout + i);
}
