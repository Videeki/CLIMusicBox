#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <cstdio>
#include <filesystem>
#include "UIHandler.h"
#include "GPIOHandler.h"
#include "PlayMusic.h"

using namespace std;
namespace fs = std::filesystem;

int main(int argc, char* argv[])
{
    string initPath = argv[2];
    vector<string> Albumlist;
    vector<string> Tracklist;


    for(const auto & entry : fs::directory_iterator(initPath))
    {
        Albumlist.push_back(entry.path().filename().string());
    }

    string songPath = initPath + "/" + Albumlist[0];

    int activeTrack = 0;
    int previousTrack = 0;
    initUI(argv[1]);
    updateTrackBar(argv[3]);
    updateAlbumBar(argv[4]);
    updateTrackList(Tracklist);

/*    do
    {
        int cmd;
        cmd = getchar();
        
        if (cmd == 0 || cmd == 224)
        {

            previousTrack = activeTrack;
            switch (cmd = getchar())
            {
            case KEY_UP:
                activeTrack--;
                break;
            case KEY_DOWN:
                activeTrack++;
                break;
            default:
                activeTrack = -1;
                cout << "Pressed key value: " << cmd;
                break;
            }
            
            updateActiceTrack(Tracklist, activeTrack, previousTrack);
        }

    } while (activeTrack >= 0);
*/
    return 0;
}