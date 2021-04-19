#include<iostream>
#include <unordered_map>
#include <string>
#include <algorithm>

//class Flyweight
//{
//private:
//    int shared_state_;

//public:
//    Flyweight( int shared_state) : shared_state_(shared_state)
//    {
//        std::cout<<"construction: shared_state_(new SharedState(*shared_state)): "<<std::endl;

//    }
//    Flyweight( Flyweight &other) : shared_state_(other.shared_state_)
//    {
//        std::cout<<"construction: shared_state_(new SharedState(*other.shared_state_)): "<<std::endl;

//    }
//};
class ATEST{
private:
    int a_t,b ;
public:
    ATEST(int a,int b):a_t(a),b(b){std::cout<<a<<std::endl;}
    ATEST(ATEST const &other):a_t(other.a_t),b(other.b){std::cout<<"con"<<std::endl;}//不加const为什么33报错，搞不懂，请指教

};
int main1(){
    int ss = 100;
    ATEST ab = ATEST(ss,ss);//不加const为什么报错，搞不懂，请指教
}
