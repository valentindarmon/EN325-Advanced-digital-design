/*
 * EN325-Advanced-digital-design teaching lab.
 * 
 * Copyright (C) { 2021 }  { Bertrand LE GAL} { Bordeaux-INP }
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
*/


#include "converter.hpp"


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
