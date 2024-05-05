#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>
#include <cstdio>
#include <filesystem>
#include <queue>
#include <functional>
#include "UIHandler.h"
#include "GPIOHandler.h"
#include "PlayMusic.h"
#include "FolderHandler.h"

using namespace std;
namespace fs = std::filesystem;

#define JUMP2INFO   "\e[33;9H"

void cmdProc(queue<string>& playlist, string musicPath);
void player(queue<string>& playlist);


int main(int argc, char* argv[])
{
    initUI(argv[1]);
    string musicPath = argv[2];
    
    queue<string> musicQueue;
    
    thread cmdProcTID(cmdProc, ref(musicQueue), musicPath);
    thread playerTID(player, ref(musicQueue));

    cmdProcTID.join();
        

    return 0;
}

void cmdProc(queue<string>& playlist, string musicPath)
{
    vector<string> Albumlist = listFolders(musicPath);
    int actAlbum = 0;
    int actTrack = 0;
    int prevTrack = 0;

    string albumPath = musicPath + "/" + Albumlist[actAlbum];
    updateAlbumBar(Albumlist[actAlbum]);

    vector<string> Tracklist = listFiles(albumPath, "mp3");
    
    string trackPath = albumPath + "/" + Tracklist[actTrack];
    updateTrackList(ref(Tracklist));
    
    refStruct gpio;
    int gpiopins[5] = {23, 24, 25, 26, 27};
    int regPINSValeus[5] = {0,0,0,0,0};

    int alert = 0;

    alert = initGPIO(&gpio, gpiopins, 5, INPUT);
    if(alert == -1)
    {
        cout << JUMP2INFO << "GPIO Init Error";
        closeGPIO(&gpio);
        return;
    }

    
    
    int sum = 0;
    do
    {
        alert = detectButtonAction(&gpio, regPINSValeus, 200);
        if(alert == -1)
        {
            cout << JUMP2INFO << "GPIO Init Error";
            closeGPIO(&gpio);
            break;
        }

        sum = 0;
        for(int i = 0; i < gpio.lines; i++)
        {
            regPINSValeus[i] *= (int)pow((double)2, (double)i);
            sum += regPINSValeus[i];
        }

        switch(sum)
        {
            case 1:     //addMusic2Playlist
            {
                playlist.push(trackPath.data());
                break;
            }

            case 2:     //stepFolderNext
            {   
                actTrack = 0;
                updateAlbumBar(Albumlist[++actAlbum]);
                albumPath = musicPath + "/" + Albumlist[actAlbum];
                Tracklist.clear();
                Tracklist = listFiles(albumPath, "mp3");
                trackPath = albumPath + "/" + Tracklist[actTrack];
                
                updateTrackList(ref(Tracklist));
                
                break;
            }

            case 4:     //stepFolderPrevious
            {
                actTrack = 0;
                updateAlbumBar(Albumlist[--actAlbum]);
                albumPath = musicPath + "/" + Albumlist[actAlbum];
                Tracklist.clear();
                Tracklist = listFiles(albumPath, "mp3");
                trackPath = albumPath + "/" + Tracklist[actTrack];
                
                updateTrackList(ref(Tracklist));

                break;
            }

            case 8:     //stepSoundNext
            {
                prevTrack = actTrack++;
                trackPath = albumPath + "/" + Tracklist[actTrack];
                updateActiveTrack(ref(Tracklist), actTrack, prevTrack);

                break;
            }

            case 16:    //stepSoundPrevious
            {
                prevTrack = actTrack--;
                trackPath = albumPath + "/" + Tracklist[actTrack];
                updateActiveTrack(ref(Tracklist), actTrack, prevTrack);
                
                break;
            }

            case 31:    //Ultimate combo
            {
                puts("Ultimate combo!");
                playlist.push("__STOP__");
            }

            default:
            {
                cout << JUMP2INFO;
                printf("NO... NO... Nem lenni! Érték lenni: %d", sum);
            }
        }
    } while (sum != 31);
    
    
    closeGPIO(&gpio);
}

void player(queue<string>& playlist)
{
    bool run = true;
    Player player;
    initMusic(&player);

    do
    {
        if(playlist.empty())
        {
            sleep(1);
        }
        else
        {
            //updateTrackBar(Tracklist[actTrack]);

            string nextSong = playlist.front();
            playlist.pop();
            
            if(nextSong == "__STOP__")
            {
                run = false;
            }
            else
            {
                //Update Current song.

                cout << JUMP2INFO;
                playMusic(&player, nextSong.data()); 
            }

            
        }

    } while (run);
    
    closeMusic(&player);

}