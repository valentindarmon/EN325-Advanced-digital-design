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

#include "encoder.hpp"

#include "../color/RGB2YUV.hpp"
#include "../dct2d/dct2d.hpp"
#include "../packing/unpacking.hpp"
#include "../quantizer/quantize.hpp"
#include "../zigzag/zigzag.hpp"

void encoder(const uint8_t RGB[192], int16_t YUV[192])
{
#pragma HLS INLINE off
    int16_t  buff_yuv [192];
    int16_t  buff_YUVf[192];
    int16_t  buff_YUVq[192];

      RGB2YUV_full(RGB,       buff_yuv);
    wang_fdct_full(buff_yuv,  buff_YUVf);
     quantize_full(buff_YUVf, buff_YUVq);
       zigzag_full(buff_YUVq, YUV);
}
