/*************************************************************************************************/
/*                                                                                               */
/*   Source: http://hzqtc.github.io/2012/05/play-mp3-with-libmpg123-and-libao.html               */
/*   Help: https://stackoverflow.com/questions/26007700/play-mp3-on-raspberry-with-mpg123-and-c  */
/*         https://snapcraft.io/install/mpg123-cm/raspbian                                       */
/*   Install -> Linux:  sudo apt-get install libao-dev                                           */
/*                      sudo apt-get install libmpg123-dev                                       */
/*                                                                                               */
/*                                                                                               */
/*   Compiling -> Linux: gcc -O2 PlayMusic.c -o PlayMusic -lmpg123 -lao                          */
/*   Compiling -> Windows: gcc PlayMusic.c -o PlayMusic.exe -lwinmm                              */
/*                                                                                               */
/*************************************************************************************************/
#include "PlayMusic.h"


int initMusic(Player* player)
{
    #ifdef _WIN32
        // Not neccesary the initialization //

    #elif __linux__
        // initializations //
        int err;

        ao_initialize();
        player->driver = ao_default_driver_id();
        mpg123_init();
        player->mh = mpg123_new(NULL, &err);
        player->buffer_size = mpg123_outblock(player->mh);
        player->buffer = (unsigned char*) malloc(player->buffer_size * sizeof(unsigned char));
    #else
        printf("Sorry, the system are not implemented yet... :'(\n")

    #endif

    return 0;
}

int playMusic(Player* player, char *path)
{
    #ifdef _WIN32
        char cmd[1024];
        sprintf(cmd, "open \"%s\" type mpegvideo alias mp3", path);
        
        mciSendString(cmd, NULL, 0, NULL);
    
        mciSendString("play mp3 wait", NULL, 0, NULL);

        mciSendString("close mp3", NULL, 0, NULL);

    #elif __linux__
        int channels, encoding;
        long rate;
        size_t done;
        ao_sample_format format;
        // open the file and get the decoding format //
        mpg123_open(player->mh, path);
        mpg123_getformat(player->mh, &rate, &channels, &encoding);

        // set the output format and open the output device //
        format.bits = mpg123_encsize(encoding) * BITS;
        format.rate = rate;
        format.channels = channels;
        format.byte_format = AO_FMT_NATIVE;
        format.matrix = 0;
        player->dev = ao_open_live(player->driver, &format, NULL);

        // decode and play //
        while (mpg123_read(player->mh, player->buffer, player->buffer_size, &done) == MPG123_OK)
            ao_play(player->dev, (char*)player->buffer, done);

    #else
        printf("Sorry, the system are not implemented yet... :'(\n")

    #endif

    return 0;
}

int closeMusic(Player* player)
{
    #ifdef _WIN32
        // Not neccesary the initialization //

    #elif __linux__
        // clean up //
        free(player->buffer);
        ao_close(player->dev);
        mpg123_close(player->mh);
        mpg123_delete(player->mh);
        mpg123_exit();
        ao_shutdown();

    #else
        printf("Sorry, the system are not implemented yet... :'(\n")

    #endif

    return 0;
}
