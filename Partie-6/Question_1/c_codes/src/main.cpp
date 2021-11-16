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

#include "./tools/bmp.hpp"
#include "./tools/analysis.hpp"
#include "./tools/converter.hpp"
#include "./tools/img_diff.hpp"

#include "./color/RGB2YUV.hpp"
#include "./color/YUV2RGB.hpp"

#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60

void printProgress(int32_t value, int32_t max)
{
    double percentage = (float)value / (float)max;
    int val  = (int) (percentage * 100);
    int lpad = (int) (percentage * PBWIDTH);
    int rpad = PBWIDTH - lpad;
    printf("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
    fflush(stdout);
}

int main(int argc, char* argv[])
{
	//
	// On charge l'image BMP en entrée du systeme
	//

    BMP pic_in ("./PictureIn.bmp");


    //
    // On calcule les differentes constantes liées à l'image
    //

    const uint32_t width  = pic_in.bmp_info_header.width;
    const uint32_t height = pic_in.bmp_info_header.height;
    const uint32_t pixels = width * height;
    const uint32_t bytes  = 3 * pixels;


    //
    // On prepare la structure de données qui va contenir les
    // données RGB dans l'ordre des macro-blocs
    //

    uint8_t* ptr_in_rgb  = (uint8_t*)malloc(bytes * sizeof(uint8_t));

    convert(ptr_in_rgb, pic_in);


    //
    // On prepare la structure de données qui va contenir les
    // données RGB dans l'ordre des macro-blocs
    //

    uint8_t* ptr_ou_rgb  = (uint8_t*)malloc(bytes * sizeof(uint8_t));


    //
    // On crée une image BMP en sortie afin de vérifier le couple
    // encodeur + decodeur
    //

    BMP pic_out(width, height);


    //
    // On declare proprement les buffers nécessaires entre les
    // différentes fonction pour le stockage des données
    //

    uint8_t buff_yuv[192];

    uint8_t* ptr_in  = ptr_in_rgb;
    uint8_t* ptr_out = ptr_ou_rgb;

    for (uint32_t ptr = 0; ptr < bytes; ptr += 192)
    {
        RGB2YUV( ptr_in,   buff_yuv );

        YUV2RGB( buff_yuv, ptr_out  );

        ptr_in  += 192;
        ptr_out += 192;

        if( ptr%192 == 0 )
            printProgress(ptr, bytes);
    }
    printf("\n");

    //
    // On transforme proprement le flot RGB organise en flux de
    // MB en un flux de pixel represenant une image RGB classique
    //

    convert(pic_out, ptr_ou_rgb);


    //
    // On memorise l'image de sortie (encodeur + decodeur) au format
    // BMP pour pouvoir vérifier que les transformations et les transformations
    // inverses sont bien codées.
    //

    analysis(pic_in, pic_out);

    img_diff(pic_in, pic_out);

    pic_out.write( "PictureOut.bmp" );

    return EXIT_SUCCESS;
}
