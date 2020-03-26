#include <iostream>
using namespace std;
#include"insertion.h"



int main(int argc, char *argv[])
{
    int a[] = {49, 38, 65, 97, 76, 13, 27, 49, 78, 34, 12, 64, 1};
//    int a[] = {8,9,1,7,2,3,5,4,6,0};

    for (int i:a)
    {
        std::cout<<i<<" ";
    }
    std::cout<<std::endl;
//    insertion(a,sizeof(a));
    bubbleSortTest(a,sizeof(a));
    for (int i:a)
    {
        std::cout<<i<<" ";
    }

    std::cout<<std::endl;
    return 0;
}


