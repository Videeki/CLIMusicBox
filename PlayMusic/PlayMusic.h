#ifndef PLAYMUSIC_H
#define PLAYMUSIC_H

#define PLAYMUSIC_VERSION_MAJOR     0
#define PLAYMUSIC_VERSION_MINOR     2
#define PLAYMUSIC_VERSION_PATCH     1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
	#include <windows.h>
    #include <mmsystem.h>

#elif __linux__
	#include <ao/ao.h>
    #include <mpg123.h>
    #define BITS 8

    typedef struct Player{
        mpg123_handle *mh;
        unsigned char *buffer;
        size_t buffer_size;
        int driver;
        ao_device *dev;
    } Player;

#else
    printf("Sorry, the system are not implemented yet... :'(\n")

#endif

int initMusic(Player* self);
int playMusic(Player* self, char *path);
int closeMusic(Player* self);

#endif  /* PLAYMUSIC_H */