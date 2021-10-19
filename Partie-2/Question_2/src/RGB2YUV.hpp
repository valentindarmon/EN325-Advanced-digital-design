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

void RGB2YUV(const int32_t din[192], int32_t dout[192])
{

}

void RGB2YUV(const uint8_t din[192], int32_t dout[192])
{
    int32_t conv[3];
    for(int32_t k = 0; k < 192; k += 3)
    {
#if 0
        for(int i = 0; i < 3; i++) dout[k+i] = din[k+i];
#else
        conv[0] = din[k+0];
        conv[1] = din[k+1];
        conv[2] = din[k+2];
        RGB2YUV(conv, dout + k);
#endif
    }
}
