/**
 *
 * Initial version of the source code comes from :
 * https://github.com/sol-prog/cpp-bmp-images
 *
 */

#ifndef _IMAGE_DIFF_
#define _IMAGE_DIFF_

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

void img_diff(BMP& pic_ref, BMP& pic_out)
{
    const uint32_t width_ref  = pic_ref.bmp_info_header.width;
    const uint32_t height_ref = pic_ref.bmp_info_header.height;

    BMP picture(width_ref, height_ref);
	//
	//
	////////////////////////////////////////////////////////////////////////
	//
	//
	for(int32_t y = 0; y < height_ref; y += 1)
    {
		for(int x=0; x<width_ref; x++)
        {
			const uint8_t r = std::abs( (int32_t)pic_ref.get_pixel_r(x,y) - (int32_t)pic_out.get_pixel_r(x,y) );
			const uint8_t g = std::abs( (int32_t)pic_ref.get_pixel_g(x,y) - (int32_t)pic_out.get_pixel_g(x,y) );
			const uint8_t b = std::abs( (int32_t)pic_ref.get_pixel_b(x,y) - (int32_t)pic_out.get_pixel_b(x,y) );

			picture.set_pixel_r(x, y, r);
			picture.set_pixel_g(x, y, g);
			picture.set_pixel_b(x, y, b);
		}
	}
	//
	//
	////////////////////////////////////////////////////////////////////////
	//
	//
    picture.write( "Picture_diff_1x.bmp" );
	//
	//
	////////////////////////////////////////////////////////////////////////
	//
	//
	for(int32_t y = 0; y < height_ref; y += 1)
    {
		for(int x=0; x<width_ref; x++)
        {
			const int32_t r = 16 * (int32_t)picture.get_pixel_r(x,y);
			const int32_t g = 16 * (int32_t)picture.get_pixel_g(x,y);
			const int32_t b = 16 * (int32_t)picture.get_pixel_b(x,y);

			picture.set_pixel_r(x, y, r > 255 ? 255 : r );
			picture.set_pixel_g(x, y, g > 255 ? 255 : g );
			picture.set_pixel_b(x, y, b > 255 ? 255 : b );
		}
	}
	//
	//
	////////////////////////////////////////////////////////////////////////
	//
	//
    picture.write( "Picture_diff_16x.bmp" );
	//
	//
	////////////////////////////////////////////////////////////////////////
	//
	//
	for(int32_t y = 0; y < height_ref; y += 1)
    {
		for(int x=0; x<width_ref; x++)
        {
			const int32_t r = (int32_t)picture.get_pixel_r(x,y);
			const int32_t g = (int32_t)picture.get_pixel_g(x,y);
			const int32_t b = (int32_t)picture.get_pixel_b(x,y);

			picture.set_pixel_r(x, y, r > 0 ? 255 : 0 );
			picture.set_pixel_g(x, y, g > 0 ? 255 : 0 );
			picture.set_pixel_b(x, y, b > 0 ? 255 : 0 );
		}
	}
	//
	//
	////////////////////////////////////////////////////////////////////////
	//
	//
    picture.write( "Picture_diff_binary.bmp" );
	//
	//
	////////////////////////////////////////////////////////////////////////
	//
	//

}


#endif
