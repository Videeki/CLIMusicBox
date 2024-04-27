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
#include "UIHandler.h"
#include "GPIOHandler.h"
#include "PlayMusic.h"

using namespace std;
namespace fs = std::filesystem;

#define JUMP2INFO   "\e[33;9H"

void cmdProc(string musicPath);
void addMusicQueue();


int main(int argc, char* argv[])
{
    //initUI(argv[1]);
    initUI("/home/Videeki/Documents/GitRepos/CLIMusicBox/Utilities/Dashboard.txt");
    //string musicPath = argv[2];
    string musicPath = "/home/Videeki/Music/";
    thread cmdProcTID(cmdProc, musicPath);
    cmdProcTID.join();
        

    

    
    
    return 0;
}

void cmdProc(string musicPath)
{
    vector<string> Albumlist;
    vector<string> Tracklist;
    Player player;
    int actAlbum = 0;
    int actTrack = 0;
    int prevTrack = 0;

    for(const auto & entry : fs::directory_iterator(musicPath))
    {
        Albumlist.push_back(entry.path().filename().string());
    }
    string albumPath = musicPath + "/" + Albumlist[actAlbum];
    updateAlbumBar(Albumlist[actAlbum]);

    for(const auto & entry : fs::directory_iterator(albumPath))
    {
        Tracklist.push_back(entry.path().filename().string());
    }
    
    string trackPath = albumPath + "/" + Tracklist[actTrack];
    updateTrackList(Tracklist);
    
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

    initMusic(&player);
    
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
                updateTrackBar(Tracklist[actTrack]);
                cout << JUMP2INFO;
                playMusic(&player, trackPath.data());
                
                break;
            }

            case 2:     //stepFolderNext
            {   
                actTrack = 0;
                updateAlbumBar(Albumlist[++actAlbum]);
                albumPath = musicPath + "/" + Albumlist[actAlbum];
                Tracklist.clear();
                for(const auto & entry : fs::directory_iterator(albumPath))
                {
                    Tracklist.push_back(entry.path().filename().string());
                };
                updateTrackList(Tracklist);
                
                break;
            }

            case 4:     //stepFolderPrevious
            {
                actTrack = 0;
                updateAlbumBar(Albumlist[--actAlbum]);
                albumPath = musicPath + "/" + Albumlist[actAlbum];
                Tracklist.clear();
                for(const auto & entry : fs::directory_iterator(albumPath))
                {
                    Tracklist.push_back(entry.path().filename().string());
                };
                updateTrackList(Tracklist);

                break;
            }

            case 8:     //stepSoundNext
            {
                prevTrack = actTrack++;
                trackPath = albumPath + "/" + Tracklist[actTrack];
                updateActiceTrack(Tracklist, actTrack, prevTrack);

                break;
            }

            case 16:    //stepSoundPrevious
            {
                prevTrack = actTrack--;
                trackPath = albumPath + "/" + Tracklist[actTrack];
                updateActiceTrack(Tracklist, actTrack, prevTrack);
                
                break;
            }

            case 31:    //Ultimate combo
            {
                puts("Ultimate combo!");
            }

            default:
            {
                cout << JUMP2INFO;
                printf("NO... NO... Nem lenni! Érték lenni: %d", sum);
            }
        }
    } while (sum != 31);
    
    closeMusic(&player);
    closeGPIO(&gpio);
}