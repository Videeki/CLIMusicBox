#define KEY_UP                  72
#define KEY_DOWN                80
#define KEY_LEFT                75
#define KEY_RIGHT               77

#define BF_BLACK                30
#define BF_RED                  31
#define BF_GREEN                32
#define BF_YELLOW               33
#define BF_BLUE                 34
#define BF_MAGENTA              35
#define BF_CYAN                 36
#define BF_WHITE                37

#define BF_CUSTOM(r, g, b) "\e[38;2;" + to_string(r) + ";" + to_string(g) + ";" + to_string(b) + "m"

#define BG_BLACK                40
#define BG_RED                  41
#define BG_GREEN                42
#define BG_YELLOW               43
#define BG_BLUE                 44
#define BG_MAGENTA              45
#define BG_CYAN                 46
#define BG_WHITE                47

#define BG_CUSTOM(r, g, b) "\e[48;2;" + to_string(r) + ";" + to_string(g) + ";" + to_string(b) + "m"

#define RESET	"\x1b[0m"

#define BOLD                    1
#define FAINT                   2
#define ITALIC                  3
#define UNDERLINE               4
#define SLOWBLINK               5
#define RAPIDBLINK              6
#define INVERT                  7
#define HIDE                    8
#define STRIKE                  9
#define PRIMARYFONT             10
#define ALTERNATIVEFONT         11

#define GOTHIC                  20
#define DOUBLEUNDERLINED        21
#define NORMALINTENSITY         22
#define NEITHERITALIC           23
#define NOTUNDERLINED           24
#define NOTBLINKING             25
#define PROPORTIONALSPACING     26
#define NOTREVERSED             27
#define REVEAL                  28
#define NOTCROSSEDOUT           29

#define HIDE_CURSOR             "\e[?25l"
#define DESIGN(bf, bg, sgr)	    "\e[" + to_string(bf) + ";" + to_string(bg) + ";" + to_string(sgr) + "m"

#define LIST_OFFSET_START_X     60
#define LIST_OFFSET_END_X       91
#define LIST_OFFSET_START_Y     11
#define MAX_LIST_LENGTH         20
#define MAX_LIST_WEIGHT         LIST_OFFSET_END_X - LIST_OFFSET_START_X

#define TRACK_OFFSET_START_X    9
#define TRACK_OFFSET_END_X      92
#define TRACK_OFFSET_START_Y    3
#define MAX_TRACK_WEIGHT        TRACK_OFFSET_END_X - TRACK_OFFSET_START_X

#define ALBUM_OFFSET_START_X    9
#define ALBUM_OFFSET_END_X      48
#define ALBUM_OFFSET_START_Y    10
#define MAX_ALBUM_WEIGHT        ALBUM_OFFSET_END_X - ALBUM_OFFSET_START_X

void initUI(const string path);
void updateTrackList(const vector<string>& tracklist);
void updateTrackBar(const string actSong);
void updateAlbumBar(const string actAlbum);
void updateActiceTrack(const vector<string>& tracklist, const int actTrack, const int prevTrack);
