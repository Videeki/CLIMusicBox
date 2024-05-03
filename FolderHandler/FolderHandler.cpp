#include "FolderHandler.h"


vector<string> listFolders(const string path)
{
    struct dirent *pDirent;
    DIR *pDir;
    vector<string> folders;


    // Ensure we can open directory.
    pDir = opendir(path.data());
    if (pDir == NULL) {
        cout << "Cannot open directory " << path << endl;
        return folders;
    }

    struct stat s;
    // Process each entry.
    while ((pDirent = readdir(pDir)) != NULL)
    {   
        string elementName = pDirent->d_name;
        string elementPath = path + '/' + elementName;

        
        if(stat(elementPath.data(), &s))   /* melyik fájlt/mappát */
        {
            cout << "Hiba, stat() sikertelen: " << elementPath << endl;
            return folders;
        }
        
        if(S_ISDIR(s.st_mode) && elementName[0] != '.')
        {
            folders.push_back(elementName);
        }
    }

    // Close directory and exit.
    closedir (pDir);

    return folders;
}


vector<string> listFiles(const string path, const string extension)
{
    struct dirent *pDirent;
    DIR *pDir;
    vector<string> files;

    // Ensure we can open directory.
    pDir = opendir (path.data());
    if (pDir == NULL) {
        cout << "Cannot open directory " << path << endl;
        return files;
    }

    // Process each entry.
    while ((pDirent = readdir(pDir)) != NULL) {
        string str = pDirent->d_name;
        size_t found = str.rfind(extension);
        if(found < str.length())
        {
            files.push_back(str);
        }
    }

    // Close directory and exit.
    closedir (pDir);

    return files;
}