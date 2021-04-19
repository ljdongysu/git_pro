from abc import ABC, abstractmethod
class Subject(ABC):
    def __init__(self):
        pass
    
    @abstractmethod
    def request(self):
        pass

class RealSubject(Subject):
    def __init__(self):
        pass

    def request(self):
        print("RealSubject: Handling request.\n")

class Proxy(Subject):
    def __init__(self,realsubject:RealSubject):
        self._realsubject = realsubject

    def request(self):
        if (self.check_access()):
            self._realsubject.request()
            self.log_acess()

    def check_access(self):
        print("Proxy: Checking access prior to firing a real request.\n")
        return True

    def log_acess(self):
        print("Proxy: Logging the time of request.\n")

def client_code(proxy:Proxy):
    proxy.request()

if __name__ == "__main__":
    real_subject = RealSubject()
    client_code(real_subject)

    proxy = Proxy(real_subject)
    client_code(proxy)