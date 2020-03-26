#ifndef READFROMDIR_H
#define READFROMDIR_H

#include <iostream>
#include "fstream"
#include <dirent.h>
#include <stdio.h>
#include <string>
#include<string.h>
#include<vector>
using namespace std;

void ReadFromDir(string dirName, vector<string>& fileNames, vector<string>& fullFileNames);
string GetStringName(string path, int type);
void CopyFile(const char *sourcefile, const char *destfile);
void ClassImg(const vector<string> &fullFileNames);

#endif // READFROMDIR_H
