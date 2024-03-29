#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <filesystem>
#include <UIHandler.h>

using namespace std;
namespace fs = std::filesystem;

int main(int argc, char* argv[])
{
    vector<string> Tracklist;

    for(const auto & entry : fs::directory_iterator(argv[2]))
    {
        Tracklist.push_back(entry.path().filename().string());
    }

    int activeTrack = 0;
    int previousTrack = 0;
    initUI(argv[1]);
    updateTrackBar(argv[3]);
    updateAlbumBar(argv[4]);
    updateTrackList(Tracklist);

    do
    {
        int cmd;
        cmd = getch();
        
        if (cmd == 0 || cmd == 224)
        {

            previousTrack = activeTrack;
            switch (cmd = getch())
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
            //updateUI(Dashboard, Tracklist, activeTrack);
            updateActiceTrack(Tracklist, activeTrack, previousTrack);
        }

    } while (activeTrack >= 0);
    
    return 0;
}