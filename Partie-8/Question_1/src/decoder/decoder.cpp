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

#include "decoder.hpp"

#include "../zigzag/izigzag.hpp"
#include "../quantizer/iquantize.hpp"

#ifdef __AVX2__
    #include "../dct2d/idct2d.hpp"
#else
    #include "../dct2d/idct2d_arm.hpp"
#endif

#include "../color/YUV2RGB.hpp"
#include "../packing/packing.hpp"


void decoder(const int16_t YUV[192], uint8_t RGB[192])
{
#pragma HLS INLINE off
    int8_t   buff_yuv[192];
    int16_t  buff_y[64], buff_Y[64], buff_Yq[64];
    int16_t  buff_u[64], buff_U[64], buff_Uq[64];
    int16_t  buff_v[64], buff_V[64], buff_Vq[64];

    izigzag(YUV, buff_Yq);
    izigzag(YUV +  64, buff_Uq);
    izigzag(YUV + 128, buff_Vq);

    i_quantize_y (buff_Yq, buff_Y);
    i_quantize_uv(buff_Uq, buff_U);
    i_quantize_uv(buff_Vq, buff_V);

    idct_simd( buff_Y, buff_y );
    idct_simd( buff_U, buff_u );
    idct_simd( buff_V, buff_v );

    pack(buff_y, buff_u, buff_v, buff_yuv);

    YUV2RGB( buff_yuv, RGB );
}
