#include <UIHandler.h>

using namespace std;
namespace fs = std::filesystem;


void initUI(const string path)
{
    //Clear the screen
    cout << "\033[1J" << "\033[1;1H";
    cout << HIDE_CURSOR;    //Hide the cursor

    string UIText;
    ifstream UIFile(path);

    while(getline(UIFile, UIText))
    {
        cout << UIText << endl;
    }
}


void updateTrackList(const vector<string>& tracklist)
{
    int i = 0;
    string substring(MAX_LIST_WEIGHT, ' ');

    int forStop = tracklist.size() > MAX_LIST_LENGTH ? MAX_LIST_LENGTH : tracklist.size();

    for(int j = 0; j < forStop; j++)
    {
        cout << "\033[" << LIST_OFFSET_START_Y + j << ";" << LIST_OFFSET_START_X << "H";
        cout << RESET << substring << RESET;
    }


    for(string track : tracklist)
    {
        if(i == MAX_LIST_LENGTH) break;

        cout << "\033[" << LIST_OFFSET_START_Y + i << ";" << LIST_OFFSET_START_X << "H";
        
        substring = track.substr(0, MAX_LIST_WEIGHT);
        substring.resize(MAX_LIST_WEIGHT, ' ');

        if(i == 0) cout << DESIGN(BF_WHITE, BG_YELLOW, BOLD);

        cout << substring << RESET << flush;

        i++;
    }
}


void updateAlbumBar(const string actAlbum)
{
    string A[3] = {" _  ", "|_| ", "| | "};
    string B[3] = {" _  ", "|_) ", "|_) "};
    string C[3] = {" __ ", "/   ", "\\__ "};
    string D[3] = {" _  ", "| \\ ", "|_/ "};
    string E[3] = {" __ ", "|_  ", "|__ "};
    string F[3] = {" __ ", "|_  ", "|   "};
    string G[3] = {" __ ", "/__ ", "\\_| "};
    string H[3] = {"    ", "|_| ", "| | "};
    string I[3] = {"___ ", " |  ", "_|_ "};
    string J[3] = {"    ", "  | ", "\\_| "};
    string K[3] = {"   ", "|/ ", "|\\ "};
    string L[3] = {"    ", "|   ", "|__ "};
    string M[3] = {"    ", "|V| ", "| | "};
    string N[3] = {"    ", "|\\| ", "| | "};
    string O[3] = {" _  ", "/ \\ ", "\\_/ "};
    string P[3] = {" _  ", "|_) ", "|   "};
    string Q[3] = {" _  ", "/ \\ ", "\\_\\ "};
    string R[3] = {" _  ", "|_) ", "| \\ "};
    string S[3] = {" __ ", "(   ", "__) "};
    string T[3] = {"___ ", " |  ", " |  "};
    string U[3] = {"    ", "| | ", "|_| "};
    string V[3] = {"     ", "\\  / ", " \\/  "};
    string W[3] = {"       ", "\\    / ", " \\/\\/  "};
    string X[3] = {"   ", "\\/ ", "/\\ "};
    string Y[3] = {"    ", "\\_/ ", " |  "};
    string Z[3] = {"___ ", " _/ ", "/__ "};


        
    for(int i = 0; i < 3; i++)
    {
        string readable;
        cout << "\033[" << ALBUM_OFFSET_START_Y + i << ";" << ALBUM_OFFSET_START_X << "H";
        for(int j = 0; j < actAlbum.length(); j++)
        {
            switch(actAlbum[j])
            {
                case 'A': readable.append(A[i]); break;
                case 'B': readable.append(B[i]); break;
                case 'C': readable.append(C[i]); break;
                case 'D': readable.append(D[i]); break;
                case 'E': readable.append(E[i]); break;
                case 'F': readable.append(F[i]); break;
                case 'G': readable.append(G[i]); break;
                case 'H': readable.append(H[i]); break;
                case 'I': readable.append(I[i]); break;
                case 'J': readable.append(J[i]); break;
                case 'K': readable.append(K[i]); break;
                case 'L': readable.append(L[i]); break;
                case 'M': readable.append(M[i]); break;
                case 'N': readable.append(N[i]); break;
                case 'O': readable.append(O[i]); break;
                case 'P': readable.append(P[i]); break;
                case 'Q': readable.append(Q[i]); break;
                case 'R': readable.append(R[i]); break;
                case 'S': readable.append(S[i]); break;
                case 'T': readable.append(T[i]); break;
                case 'U': readable.append(U[i]); break;
                case 'V': readable.append(V[i]); break;
                case 'W': readable.append(W[i]); break;
                case 'X': readable.append(X[i]); break;
                case 'Y': readable.append(Y[i]); break;
                case 'Z': readable.append(Z[i]); break;
                default:  readable.append("    ");
            }
        }
        if(readable.length() > MAX_ALBUM_WEIGHT)
        {
            readable.resize(MAX_ALBUM_WEIGHT);
        }
        else
        {
            readable.resize(MAX_ALBUM_WEIGHT, ' ');
        }
        cout << readable;
    }
}


void updateTrackBar(const string actSong)
{
    string A[3] = {" _  ", "|_| ", "| | "};
    string B[3] = {" _  ", "|_) ", "|_) "};
    string C[3] = {" __ ", "/   ", "\\__ "};
    string D[3] = {" _  ", "| \\ ", "|_/ "};
    string E[3] = {" __ ", "|_  ", "|__ "};
    string F[3] = {" __ ", "|_  ", "|   "};
    string G[3] = {" __ ", "/__ ", "\\_| "};
    string H[3] = {"    ", "|_| ", "| | "};
    string I[3] = {"___ ", " |  ", "_|_ "};
    string J[3] = {"    ", "  | ", "\\_| "};
    string K[3] = {"   ", "|/ ", "|\\ "};
    string L[3] = {"    ", "|   ", "|__ "};
    string M[3] = {"    ", "|V| ", "| | "};
    string N[3] = {"    ", "|\\| ", "| | "};
    string O[3] = {" _  ", "/ \\ ", "\\_/ "};
    string P[3] = {" _  ", "|_) ", "|   "};
    string Q[3] = {" _  ", "/ \\ ", "\\_\\ "};
    string R[3] = {" _  ", "|_) ", "| \\ "};
    string S[3] = {" __ ", "(   ", "__) "};
    string T[3] = {"___ ", " |  ", " |  "};
    string U[3] = {"    ", "| | ", "|_| "};
    string V[3] = {"     ", "\\  / ", " \\/  "};
    string W[3] = {"       ", "\\    / ", " \\/\\/  "};
    string X[3] = {"   ", "\\/ ", "/\\ "};
    string Y[3] = {"    ", "\\_/ ", " |  "};
    string Z[3] = {"___ ", " _/ ", "/__ "};


        
    for(int i = 0; i < 3; i++)
    {
        string readable;
        cout << "\033[" << TRACK_OFFSET_START_Y + i << ";" << TRACK_OFFSET_START_X << "H";
        for(int j = 0; j < actSong.length(); j++)
        {
            switch(actSong[j])
            {
                case 'A': readable.append(A[i]); break;
                case 'B': readable.append(B[i]); break;
                case 'C': readable.append(C[i]); break;
                case 'D': readable.append(D[i]); break;
                case 'E': readable.append(E[i]); break;
                case 'F': readable.append(F[i]); break;
                case 'G': readable.append(G[i]); break;
                case 'H': readable.append(H[i]); break;
                case 'I': readable.append(I[i]); break;
                case 'J': readable.append(J[i]); break;
                case 'K': readable.append(K[i]); break;
                case 'L': readable.append(L[i]); break;
                case 'M': readable.append(M[i]); break;
                case 'N': readable.append(N[i]); break;
                case 'O': readable.append(O[i]); break;
                case 'P': readable.append(P[i]); break;
                case 'Q': readable.append(Q[i]); break;
                case 'R': readable.append(R[i]); break;
                case 'S': readable.append(S[i]); break;
                case 'T': readable.append(T[i]); break;
                case 'U': readable.append(U[i]); break;
                case 'V': readable.append(V[i]); break;
                case 'W': readable.append(W[i]); break;
                case 'X': readable.append(X[i]); break;
                case 'Y': readable.append(Y[i]); break;
                case 'Z': readable.append(Z[i]); break;
                default:  readable.append("    ");
            }
        }
        if(readable.length() > MAX_TRACK_WEIGHT)
        {
            readable.resize(MAX_TRACK_WEIGHT);
        }
        else
        {
            readable.resize(MAX_TRACK_WEIGHT, ' ');
        }
        cout << readable;
    }
}


void updateActiveTrack(const vector<string>& tracklist, const int actTrack, const int prevTrack)
{
    string substring(MAX_LIST_WEIGHT, ' ');
    if(actTrack > prevTrack)
    {
        cout << "\033[" << LIST_OFFSET_START_Y + prevTrack << ";" << LIST_OFFSET_START_X << "H";
        substring = tracklist[prevTrack].substr(0, MAX_LIST_WEIGHT);
        substring.resize(MAX_LIST_WEIGHT, ' ');
        cout << RESET;
        cout << substring << flush;
        
        cout << "\033[" << LIST_OFFSET_START_Y + actTrack << ";" << LIST_OFFSET_START_X << "H";
        substring = tracklist[actTrack].substr(0, MAX_LIST_WEIGHT);
        substring.resize(MAX_LIST_WEIGHT, ' ');
        cout << DESIGN(BF_WHITE, BG_YELLOW, BOLD);
        cout << substring << RESET << flush;
        
    }
    else if(actTrack < prevTrack)
    {
        cout << "\033[" << LIST_OFFSET_START_Y + actTrack << ";" << LIST_OFFSET_START_X << "H";
        substring = tracklist[actTrack].substr(0, MAX_LIST_WEIGHT);
        substring.resize(MAX_LIST_WEIGHT, ' ');
        cout << RESET;
        cout << substring << flush;
        
        cout << "\033[" << LIST_OFFSET_START_Y + prevTrack << ";" << LIST_OFFSET_START_X << "H";
        substring = tracklist[prevTrack].substr(0, MAX_LIST_WEIGHT);
        substring.resize(MAX_LIST_WEIGHT, ' ');
        cout << DESIGN(BF_WHITE, BG_YELLOW, BOLD);
        cout << substring << RESET << flush;
    }
    else
    {
        cout << "prevTrack: " << prevTrack << " actTrack: " << actTrack << endl; 
    }
}
