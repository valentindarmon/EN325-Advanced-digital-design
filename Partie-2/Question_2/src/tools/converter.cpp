/**
 *
 * Initial version of the source code comes from :
 * https://github.com/sol-prog/cpp-bmp-images
 *
 */

#ifndef _IMAGE_CONVERT_
#define _IMAGE_CONVERT_

#include <iostream>
#include <cmath>
#include <cstring>
#include <chrono>
#include <vector>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <getopt.h>
#include <iostream>
#include <algorithm>

using namespace std;

#include "bmp.hpp"


void convert(uint8_t* ptr_rgb, BMP& pic_in)
{
    const uint32_t width_ref  = pic_in.bmp_info_header.width;
    const uint32_t height_ref = pic_in.bmp_info_header.height;

    uint8_t* ptr_w_rgb   = ptr_rgb;

    for(int32_t y = 0; y < height_ref; y += 8)
	{
        for(int32_t x = 0; x < width_ref; x += 8)
		{
            for(int32_t yy = 0; yy < 8; yy += 1)
			{
                for(int32_t xx = 0; xx < 8; xx += 1)
				{
                    (*ptr_w_rgb++) = pic_in.get_pixel_r(x + xx, y + yy);
                    (*ptr_w_rgb++) = pic_in.get_pixel_g(x + xx, y + yy);
                    (*ptr_w_rgb++) = pic_in.get_pixel_b(x + xx, y + yy);
                }
            }
        }
    }
}


void convert(BMP& pic_out, const uint8_t* ptr_rgb)
{
    const uint32_t width_ref  = pic_out.bmp_info_header.width;
    const uint32_t height_ref = pic_out.bmp_info_header.height;

    for(int32_t y = 0; y < height_ref; y += 8)
	{
        for(int32_t x = 0; x < width_ref; x += 8)
		{
            for(int32_t yy = 0; yy < 8; yy += 1)
			{
                for(int32_t xx = 0; xx < 8; xx += 1)
				{
                    pic_out.set_pixel_r(x + xx, y + yy, (*ptr_rgb++));
                    pic_out.set_pixel_g(x + xx, y + yy, (*ptr_rgb++));
                    pic_out.set_pixel_b(x + xx, y + yy, (*ptr_rgb++));
                }
            }
        }
    }
}


#endif
