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


int initMusic(Player* self)
{
    #ifdef _WIN32
        // Not neccesary the initialization //

    #elif __linux__
        // initializations //
        int err;

        ao_initialize();
        self->driver = ao_default_driver_id();
        mpg123_init();
        self->mh = mpg123_new(NULL, &err);
        self->buffer_size = mpg123_outblock(self->mh);
        self->buffer = (unsigned char*) malloc(self->buffer_size * sizeof(unsigned char));
    #else
        printf("Sorry, the system are not implemented yet... :'(\n")

    #endif

    return 0;
}

int playMusic(Player* self, char *path)
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
        mpg123_open(self->mh, path);
        mpg123_getformat(self->mh, &rate, &channels, &encoding);

        // set the output format and open the output device //
        format.bits = mpg123_encsize(encoding) * BITS;
        format.rate = rate;
        format.channels = channels;
        format.byte_format = AO_FMT_NATIVE;
        format.matrix = 0;
        self->dev = ao_open_live(self->driver, &format, NULL);

        // decode and play //
        while (mpg123_read(self->mh, self->buffer, self->buffer_size, &done) == MPG123_OK)
            ao_play(self->dev, (char*)self->buffer, done);

    #else
        printf("Sorry, the system are not implemented yet... :'(\n")

    #endif

    return 0;
}

int closeMusic(Player* self)
{
    #ifdef _WIN32
        // Not neccesary the initialization //

    #elif __linux__
        // clean up //
        free(self->buffer);
        ao_close(self->dev);
        mpg123_close(self->mh);
        mpg123_delete(self->mh);
        mpg123_exit();
        ao_shutdown();

    #else
        printf("Sorry, the system are not implemented yet... :'(\n")

    #endif

    return 0;
}
