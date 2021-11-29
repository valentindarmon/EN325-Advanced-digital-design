#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <iostream>


#include "tools/bmp.hpp"
#include "tools/converter.hpp"
#include "tools/img_diff.hpp"
#include "tools/analysis.hpp"

#include "encoder/encoder.hpp"
#include "decoder/decoder.hpp"

#include "backend/jpeg_stream.hpp"

int main(int argc, char* argv[])
{
    printf("(II) Lauching the JPEG encoder\n");

	//
	// On charge l'image BMP en entrée du systeme
	//

    BMP pic_in ("../image/leopard.bmp");


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
    // On cree un buffer temporaire pour memoriser les données
    // post-encodeur afin de pouvoir finaliser a posteriori la
    // compression JPEG (Huffman, header, etc...)
    //

    int16_t* ptr_enc  = (int16_t*)malloc(bytes * sizeof(int16_t));
    memset( ptr_enc, 0xFF, bytes * sizeof(int16_t) );
    printf("(II) allocating a buffer of : %6d elements\n", bytes);
    printf("(II) allocating a buffer of : %6lu bytes\n", bytes * sizeof(int16_t));

    //
    // On declare proprement les buffers nécessaires entre les
    // différentes fonction pour le stockage des données
    //

#if 0
    int8_t   buff_yuv[192];
    int16_t  buff_y[64], buff_Y[64], buff_Yq[64], buff_Yz[64];
    int16_t  buff_u[64], buff_U[64], buff_Uq[64], buff_Uz[64];
    int16_t  buff_v[64], buff_V[64], buff_Vq[64], buff_Vz[64];
#endif

    int16_t stream[192];

    uint8_t* ptr_in  = ptr_in_rgb;
    uint8_t* ptr_out = ptr_ou_rgb;

    for (uint32_t ptr = 0; ptr < bytes; ptr += 192)
    {
        //
        // On realise l'opération d'encodage des données
        //

#if 1
        encoder( ptr_in, stream );
        memcpy(ptr_enc + ptr, stream, 192 * sizeof(int16_t));
#else
        RGB2YUV( ptr_in, buff_yuv  );

        unpack(buff_yuv, buff_y, buff_u, buff_v);

        wang_fdct( buff_y, buff_Y );
        wang_fdct( buff_u, buff_U );
        wang_fdct( buff_v, buff_V );

        quantize_q( buff_Y, buff_Yq);
        quantize_uv(buff_U, buff_Uq);
        quantize_uv(buff_V, buff_Vq);

        zigzag(buff_Yq, buff_Yz);
        zigzag(buff_Uq, buff_Uz);
        zigzag(buff_Vq, buff_Vz);

        //
        // On memorise les informations sorties de l'encodeur afin
        // de pouvoir terminer la création du fichier JPEG à postériori
        //

        memcpy(ptr_enc + ptr,       buff_Yz, 64 * sizeof(int16_t));
        memcpy(ptr_enc + ptr +  64, buff_Uz, 64 * sizeof(int16_t));
        memcpy(ptr_enc + ptr + 128, buff_Vz, 64 * sizeof(int16_t));
#endif
        //
        // On realise l'opération de décodage des données
        //

#if 1
        decoder( stream, ptr_out );
#else
        izigzag(buff_Yz, buff_Yq);
        izigzag(buff_Uz, buff_Uq);
        izigzag(buff_Vz, buff_Vq);

        i_quantize_y (buff_Yq, buff_Y);
        i_quantize_uv(buff_Uq, buff_U);
        i_quantize_uv(buff_Vq, buff_V);

        idct_simd( buff_Y, buff_y );
        idct_simd( buff_U, buff_u );
        idct_simd( buff_V, buff_v );

        pack(buff_y, buff_u, buff_v, buff_yuv);

        YUV2RGB( buff_yuv, ptr_out );
#endif
        ptr_in  += 192;
        ptr_out += 192;
    }

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

    pic_out.write( "SavePicture.bmp" );


    //
    // On transforme proprement le flot YUV organisé en flux de
    // MB sous la forme d'un vrai fichier JPEG
    //

    jpeg_stream( ptr_enc, width, height );

    free( ptr_enc );

    return EXIT_SUCCESS;
}
