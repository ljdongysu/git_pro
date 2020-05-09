#include <QCoreApplication>
#include<iostream>
#include<string>
#include<fstream>
#include <stdlib.h>
#include <sstream>     // std::stringstream
using namespace std;
typedef unsigned long long FRAME_NUM_TYPE;

std::string strToHex(std::string str, std::string separator = "")
{
    const std::string hex = "0123456789ABCDEF";
    std::stringstream ss;

    for (std::string::size_type i = 0; i < str.size(); ++i)
        ss << hex[(unsigned char)str[i] >> 4] << hex[(unsigned char)str[i] & 0xf] << separator;

    return ss.str();
}

//从文件读入到string里
string readFileIntoString(char * filename)
{
ifstream ifile(filename);
//将文件读入到ostringstream对象buf中
ostringstream buf;
char ch;
while(buf&&ifile.get(ch))
buf.put(ch);
//返回与流对象buf关联的字符串
return buf.str();
}

string add0xDot(string sss)
{

    string result = "";
    for (size_t i = 0; i < sss.length(); ++i)
    {
        if (i%2 ==0)
        {
            result += "0x";
            result += sss[i];
        }
        else
        {
            result += sss[i];
            if (i!=sss.length()-1)
            {
                result += ',';
            }
        }
    }
    return result;
}
//string readFileIntoStringdiv(char * filename,string content)
//{
//    string fileString = readFileIntoString(filename);
//    string result = "";
////    cout<<fileString<<endl;
////    cout<<"fileString: "<<fileString.length()<<endl;
////    cout<<"last}:"<<fileString.find_last_of('}')<<endl;
//    for (size_t i = 0; i < fileString.length(); ++i)
//    {
//        if (fileString[i] == '{')
//        {
//            result += fileString[i];
//            while(fileString[i]!='}')
//            {
//                ++i;
//            }
////            cout<<i<<endl;
//            if (fileString[i] == '}')
//            {
//                result += content;
//            }
//        }
////        cout<<"last{:"<<i<<" "<<fileString[i]<< endl;
//        result += fileString[i];
//    }
//    return result;

//}

bool GetInput(int argc, char *argv[], char* video)
{
    if (argc != 2)
    {
        std::cout << "\033[31mPlease input parameter!\033[30m" << std::endl;
        return false;
    }
    else
    {
        sscanf(argv[1], "%s", video);
    }

    return true;
}

int main(int argc, char *argv[])
{
    char contentCu[200] = "content.txt";
    char resultCpp[200] = "vectorAdd.cpp";
    if (!GetInput(argc, argv,contentCu))
    {
        cout<<"please input .cu filename"<<endl;
        cout<<"error!"<<endl;
        return 0;
    }

    string sss = readFileIntoString(contentCu);

    string s = strToHex(sss);
//    cout<<"s:"<<s<<endl;

    string result = add0xDot(s);
//    cout<<result <<endl;
//    cout<<s.length()<<endl;
//    cout<<result.length()<<endl;

//    string wresult = readFileIntoStringdiv(originalCpp,result);
    string wresult = "#include <string>\nstd::string m_ptx_source = {" + result + "};";
    ofstream outfile;
    outfile.open(resultCpp);
    for (size_t i = 0; i < wresult.length(); ++i)
    {
        stringstream ss;
        ss << wresult[i];
        outfile << ss.str();
    }
    outfile.close();
    return 0;

}
