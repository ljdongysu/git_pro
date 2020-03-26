#include"readfromdir.h"
#include <sys/stat.h>
#include <sys/types.h>

int main()
{
    string dirName = "/home/ljdong/code/qt/dna_data/imageDataset/kFrame/";
    vector<string> fileNames;
    vector<string> fullFileNames;
//    ReadFromDir(dirName,fileNames,fullFileNames);

//    ClassImg(fullFileNames);
    ReadFromDir("/home/ljdong/code/qt/dna_data/imageDataset/refer/",fileNames,fullFileNames);

    cout<<fileNames.size()<<endl;
}
