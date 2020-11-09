#include <QCoreApplication>
#include <exception>
#include <stdexcept>
#include <iostream>
class MyExpection : public std::exception
{
public:
        const char* what()const throw()
//函数后面必须跟throw(),括号里面不能有任务参数，表示不抛出任务异常
//因为这个已经是一个异常处理信息了，不能再抛异常。
        {
                return "MyException";
        }

};
void test1()
{
    int a =1;
    try {
        int c =1;
        throw MyExpection();
    } catch (std::runtime_error & e) {
        std::cout<<"in test 1"<<std::endl;
        throw std::runtime_error("1111111111");
    }
    std::cout<<"222222222222222222222222"<<std::endl;
}
int main(int argc, char *argv[])
{   try{
    test1();
    }
    catch(...)
    {
        std::cout<<"in Main()"<<std::endl;
    }
    return 0;
}
