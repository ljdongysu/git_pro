#include"strToCh.h"
std::string charToStr(char *s)
{
    string result = s;
    return result;
}
std::string charArrToStr(char a[])
{
    string result = a;
    return result;
}

char *strToChar(std::string s)
{
    char * result = (char *)s.c_str();
    return result;
}

const char *strToConstChar(std::string s)
{
    const char * resulut = s.c_str();
    return resulut;
}

