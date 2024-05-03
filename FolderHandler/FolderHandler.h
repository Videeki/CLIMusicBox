#ifndef FOLDERHANDLER_H
#define FOLDERHANDLER_H

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

using namespace std;
vector<string> listFolders(const string path);
vector<string> listFiles(const string path, const string extension);

#endif  /* FOLDERHANDLER_H */