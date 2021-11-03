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

void YUV2RGB(const int32_t din[192], int32_t dout[192])
{

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
