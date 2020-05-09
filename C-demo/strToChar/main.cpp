#include <QCoreApplication>
#include"strToCh.h"
#include<iostream>
using namespace std;
int main(int argc, char *argv[])
{
    string s = "abcde\n";
    cout<< s<<endl;
    char * s1 = strToChar(s);
    cout<<s1<<endl;
    const char *a = strToConstChar(s);
    cout<<a<<endl;
    string s2 = charToStr(s1);
    cout<<s2<<endl;
    char aa[100];
    strcpy(aa,strToChar(s));
    cout<<aa<<endl;
    return 0;
}
