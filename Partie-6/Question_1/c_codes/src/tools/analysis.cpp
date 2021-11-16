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

#include "analysis.hpp"

inline double sqr(int32_t v)
{
    return v * v;
}

void analysis(BMP& pic_ref, BMP& pic_out)
{
	int32_t min_error[3] = {256, 256, 256};
	int32_t max_error[3] = {  0,   0,   0};

	double  avg_error[3] = {  0,   0,   0};
	double  mse_error[3] = {  0,   0,   0};

    const uint32_t width_ref  = pic_ref.bmp_info_header.width;
    const uint32_t height_ref = pic_ref.bmp_info_header.height;

    const uint32_t width_out  = pic_out.bmp_info_header.width;
    const uint32_t height_out = pic_out.bmp_info_header.height;

    if( width_ref != width_out )
    {        
		printf("assertion( width_ref != width_out )\n");
        exit( EXIT_FAILURE );
    }

    if( height_ref != height_out )
    {
		printf("assertion( height_ref != height_out )\n");
        exit( EXIT_FAILURE );
    }

	for(int32_t y = 0; y < height_ref; y += 1)
    {
		for(int x=0; x<width_ref; x++)
        {
			const int32_t r = std::abs((int32_t)pic_ref.get_pixel_r(x,y) - (int32_t)pic_out.get_pixel_r(x,y));
			const int32_t g = std::abs((int32_t)pic_ref.get_pixel_g(x,y) - (int32_t)pic_out.get_pixel_g(x,y));
			const int32_t b = std::abs((int32_t)pic_ref.get_pixel_b(x,y) - (int32_t)pic_out.get_pixel_b(x,y));

			min_error[0]  = std::min(min_error[0], r );
			min_error[1]  = std::min(min_error[1], g );
			min_error[2]  = std::min(min_error[2], b );

			max_error[0]  = std::max(max_error[0], r );
			max_error[1]  = std::max(max_error[1], g );
			max_error[2]  = std::max(max_error[2], b );

			avg_error[0] += std::abs( r );
			avg_error[1] += std::abs( g );
			avg_error[2] += std::abs( b );

			mse_error[0] += sqr( std::abs( r ) );
			mse_error[1] += sqr( std::abs( g ) );
			mse_error[2] += sqr( std::abs( b ) );
		}
	}

	avg_error[0] /= (width_ref * height_ref);
	avg_error[1] /= (width_ref * height_ref);
	avg_error[2] /= (width_ref * height_ref);

	mse_error[0] /= (width_ref * height_ref);
	mse_error[1] /= (width_ref * height_ref);
	mse_error[2] /= (width_ref * height_ref);

	cout << "MIN/MAX PIXEL ERROR :" << endl;
	cout << " - RED   CHANNEL [" << min_error[0] << ", " << max_error[0] << "]" << endl;
	cout << " - GREEN CHANNEL [" << min_error[1] << ", " << max_error[1] << "]" << endl;
	cout << " - BLUE  CHANNEL [" << min_error[2] << ", " << max_error[2] << "]" << endl;

	cout << "AVERAGE VALUE ERROR :" << endl;
	cout << " - RED   CHANNEL [" << avg_error[0] << " err/pixel]" << endl;
	cout << " - GREEN CHANNEL [" << avg_error[1] << " err/pixel]" << endl;
	cout << " - BLUE  CHANNEL [" << avg_error[2] << " err/pixel]" << endl;

	cout << "MSE VALUE ERROR :" << endl;
	cout << " - RED   CHANNEL [" << sqrt(mse_error[0]) << " err/pixel]" << endl;
	cout << " - GREEN CHANNEL [" << sqrt(mse_error[1]) << " err/pixel]" << endl;
	cout << " - BLUE  CHANNEL [" << sqrt(mse_error[2]) << " err/pixel]" << endl;

	cout << "Picture SNR VALUES :" << endl;
	cout << " - RED   CHANNEL [" << (10.0 * log10((255.0*255.0) / mse_error[0])) << " dB]" << endl;
	cout << " - GREEN CHANNEL [" << (10.0 * log10((255.0*255.0) / mse_error[1])) << " dB]" << endl;
	cout << " - BLUE  CHANNEL [" << (10.0 * log10((255.0*255.0) / mse_error[2])) << " dB]" << endl;
}
