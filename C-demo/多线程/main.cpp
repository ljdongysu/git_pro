#include<iostream>
#include<thread>
#define SLEEP_S(x) std::this_thread::sleep_for(std::chrono::seconds((x)))

class testThread{

public:
void  Start();

};


std::thread testThread1;
void testThread::Start()
{
	
	testThread1 = std::thread(
	[this](){
		while(1){
			
			std::cout<<"time sleep: "<<std::endl;
			std::cout<<"time sleep1: "<<std::endl;
			std::cout<<"time sleep2: "<<std::endl;
			std::cout<<"time sleep3: "<<std::endl;
                      // SLEEP_S(1);

		}
	
	});
	testThread1.detach();
}
int main(){
std::cout<<"start\n";
testThread *testthread = new testThread();
std::cout<<"after new\n";
testthread->Start();
std::cout<<"after Start()\n";
return 0;

}
