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


#include "bmp.hpp"
#include "RGB2YUV.hpp"
#include "YUV2RGB.hpp"

int main(int argc, char* argv[])
{
	//
	// On charge l'image BMP en entrée du systeme
	//

    BMP pic_in ("./ImageEntree.bmp");


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
    uint8_t* ptr_w_rgb   = ptr_in_rgb;

    for(int32_t y = 0; y < height; y += 8){
        for(int32_t x = 0; x < width; x += 8){
            for(int32_t yy = 0; yy < 8; yy++){
                for(int32_t xx = 0; xx < 8; xx++){
                    (*ptr_w_rgb++) = pic_in.get_pixel_r(x + xx, y + yy);
                    (*ptr_w_rgb++) = pic_in.get_pixel_g(x + xx, y + yy);
                    (*ptr_w_rgb++) = pic_in.get_pixel_b(x + xx, y + yy);
                }
            }
        }
    }


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
    // On cree un buffer temporaire pour memoriser les données
    // post-encodeur afin de pouvoir finaliser a posteriori la
    // compression JPEG (Huffman, header, etc...)
    //

    //
    // On declare proprement les buffers nécessaires entre les
    // différentes fonction pour le stockage des données
    //

    int32_t buff_yuv[192];

    uint8_t* ptr_in  = ptr_in_rgb;
    uint8_t* ptr_out = ptr_ou_rgb;

    for (uint32_t ptr = 0; ptr < bytes; ptr += 192)
    {
        RGB2YUV( ptr_in,   buff_yuv );
        YUV2RGB( buff_yuv, ptr_out  );

        ptr_in  += 192;
        ptr_out += 192;
    }

    //
    // On transforme proprement le flot RGB organise en flux de
    // MB en un flux de pixel represenant une image RGB classique
    //

    uint8_t* ptr_r_rgb = ptr_ou_rgb;
    for(int32_t y = 0; y < height; y += 8){
        for(int32_t x = 0; x < width; x += 8){
            for(int32_t yy = 0; yy < 8; yy++){
                for(int32_t xx = 0; xx < 8; xx++){
                    pic_out.set_pixel_r(x + xx, y + yy, (*ptr_r_rgb++));
                    pic_out.set_pixel_g(x + xx, y + yy, (*ptr_r_rgb++));
                    pic_out.set_pixel_b(x + xx, y + yy, (*ptr_r_rgb++));
                }
            }
        }
    }


    //
    // On memorise l'image de sortie (encodeur + decodeur) au format
    // BMP pour pouvoir vérifier que les transformations et les transformations
    // inverses sont bien codées.
    //

    pic_out.write( "SavePicture.bmp" );

    return EXIT_SUCCESS;
}
