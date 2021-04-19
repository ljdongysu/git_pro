#include <iostream>
#include <vector>
class Product{
public:
    std::vector<std::string> namelist;
    void print_namelist()
    {
        std::cout<<"1"<<std::endl;
    }
    void push_f(){
        namelist.push_back("xxx");
    }
};
class Prodetc1{
public:
    Product *product;
    Prodetc1(){sert();}
    void sert(){
    product = new Product();}
    Product* getProduct(){
        product->namelist.push_back("4");
        product->namelist.push_back("8");
        product->namelist.push_back("12");

    return product;
}
};
int main(){
    Prodetc1 *p = new Prodetc1();
    Product *p1 = p->getProduct();
    std::cout<<p1<<std::endl;
    std::cout<<p->product<<std::endl;
    std::cout<<p1->namelist.size()<<std::endl;
    std::cout<<p->product->namelist.size()<<std::endl;

    p->sert();

    std::cout<<p1<<std::endl;
    std::cout<<p->product<<std::endl;
    std::cout<<p1->namelist.size()<<std::endl;
    std::cout<<p->product->namelist.size()<<std::endl;

}
