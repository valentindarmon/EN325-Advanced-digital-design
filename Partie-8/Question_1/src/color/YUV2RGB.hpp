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
#ifndef _YUV2RGB_
#define _YUV2RGB_

#include <cstdio>
#include <cstdlib>
#include <cstdint>

#define MIN(a,b) ((a<b)?a:b)
#define MAX(a,b) ((a<b)?b:a)
#define LIMIT(a,b,c) MIN(MAX(a,b),c)


void YUV2RGB(const int8_t din[192], uint8_t dout[192])
{
    for (int32_t i = 0; i < 192; i += 3)
    {
        const int32_t y = din[i+0] + 128;
        const int32_t u = din[i+1];
        const int32_t v = din[i+2];

        int32_t r = (y * 256 + v * 359          + 128) >> 8;
        int32_t g = (y * 256 - u * 88 - v * 182 + 128) >> 8;
        int32_t b = (y * 256 + u * 454          + 128) >> 8;

             if (r <   0) r =   0;
        else if (r > 255) r = 255;

             if (g <   0) g =   0;
        else if (g > 255) g = 255;

             if (b <   0) b =   0;
        else if (b > 255) b = 255;

        dout[i+0] = r;
        dout[i+1] = g;
        dout[i+2] = b;
    }
}

#endif
