#include<iostream>
class Graphic{
    void draw();
};
class Shape:public Graphic{
    int x;
public:
    void draw();
};
class Dot:public Graphic{
public:
    void draw();
};
class Exporter{
public:
    void exporter(Shape s){
        std::cout<<"dao chu yuan xing!"<<std::endl;
    }
    void exporter(Dot d){
        std::cout<<"dao chu Dot!"<<std::endl;
    }
};
class App{
public:
    void exporter(Shape shape){
        Exporter exporter =  Exporter();
        exporter.exporter(shape);
    }
};
int main()
{
    App app = App();
    app.exporter(*new Shape());

}
