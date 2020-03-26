#include"readfromdir.h"
#include <sys/stat.h>
#include <sys/types.h>

void ReadFromDir(string dirName, vector<string>& fileNames, vector<string>& fullFileNames)
{
    DIR * dir;
    struct dirent * ptr;
    int i=0;
    string rootdirPath = dirName;
    string x,dirPath;
    dir = opendir((char *)rootdirPath.c_str()); //打开一个目录

    struct stat s;
    while((ptr = readdir(dir)) != NULL) //循环读取目录数据
    {

        x=ptr->d_name;
        cout<<x<<endl;
        cout<<endl;
        if (strcmp(x.c_str(),".") == 0 || strcmp(x.c_str(),"..") == 0)
        {
            continue;
        }
        dirPath = rootdirPath + x;
        stat(dirPath.c_str() , &s ) ;
        printf("d_name : %s\n", ptr->d_name); //输出文件名

        if(s.st_mode & S_IFDIR)
        {
            dirPath = dirPath + "/";
            ReadFromDir(dirPath,fileNames,fullFileNames);
        }else if(s.st_mode & S_IFREG)
        {
            fileNames.push_back(x);
            fullFileNames.push_back(dirPath);
            printf("d_name : %s\n", dirPath.c_str()); //输出文件绝对路径
            ++i;
        }
    }

    cout<<"all file size: "<<i<<endl;

    closedir(dir);
}



std::string GetStringName(string path, int type)
{
    //0:path   1:path + file  2: file.jpg  3:file
    if (type ==0)
    {
    string::size_type startPosition = path.find_last_of('/') + 1;
    string fileName = path.substr(startPosition, path.length() - startPosition);

    return fileName;
    }
    else if (type ==1)
    {
        string name = path.substr(0, path.rfind("."));

        return name;
    }
    else if(type==2)
    {
        string suffixStr = path.substr(path.find_last_of('.') + 1);

        return suffixStr;
    }
    if (type ==3)
    {
    string::size_type startPosition = path.find_last_of('/') + 1;
    string::size_type endPosition = path.find_last_of('.');
    string fileName = path.substr(startPosition, endPosition-startPosition);

    return fileName;
    }
    else
    {
        std::cout<<"error type"<<std::endl;
    }
}


void CopyFile(const char* sourcefile, const char* destfile)
{
    string command = "cp ";
    command  += sourcefile;
    command  += " ";
    command  += destfile;//cp /home/file1 /root/file2
    system((char*)command.c_str());//
}


void ClassImg(const vector<string >& fullFileNames)
{
    vector<bool> referFlag(fullFileNames.size(),true);

    for (int i = 0;i < fullFileNames.size(); ++i)
    {
        string fileName = GetStringName(fullFileNames[i],3);

        string::size_type startPosition = fileName.find_last_of('_');
        string className = fileName.substr(0,startPosition);
        cout<<"className: "<<className<<endl;
        string imgName = fileName.substr(startPosition+1);
        cout<<"imgName: "<<imgName<<endl;

        if (referFlag[std::stoi(className)])
        {
            fileName = "/home/ljdong/code/qt/dna_data/imageDataset/refer/Parasite/" + className;
            mkdir(fileName.c_str(),S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
//            std::cout<<"mkdir refer name :"<<fileName<<endl;

            fileName = fileName + "/" + imgName + ".jpg";
            CopyFile(fullFileNames[i].c_str(), fileName.c_str());

//            std::cout<<"write refer name :"<<fileName<<endl;
            referFlag[std::stoi(className)] = false;
        }
        else
        {
            fileName = "/home/ljdong/code/qt/dna_data/imageDataset/train/Parasite/" + className;
            mkdir(fileName.c_str(),S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

            std::cout<<"mkdir train name :"<<fileName<<endl;

            fileName = fileName + "/" + imgName + ".jpg";

            CopyFile(fullFileNames[i].c_str(), fileName.c_str());

//            std::cout<<"write train name :"<<fileName<<endl;
//            std::cout<<endl;

        }

    }
}
