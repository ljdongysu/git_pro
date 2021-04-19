class SubSystem1():
    def __init__(slef):
        pass
    def operation1(self)->str:
        return "Subsystem1: Ready!\n"
    def operation2(self)->str:
        return "Subsystem1: Go!\n"
class SubSystem2():
    def __init__(self):
        pass
    def operation1(self)->str:
        return "Subsystem2: Ready!\n"
    def operation2(self)->str:
        return "Subsystem2: Go!\n"
class Facade:
    def __init__(self,sub_system1:SubSystem1,sub_system2:SubSystem2):
        self._sub_system1 = sub_system1
        self._sub_system2 = sub_system2
    def operation(self)->str:
        result = "Facade initializes subsystems:\n"
        result += self._sub_system1.operation1() 
        result += self._sub_system1.operation2()
        result += "Facade orders subsystems to perform the action:\n"
        result += self._sub_system2.operation1()
        result += self._sub_system2.operation2()
        return result

def client_code(faceade:Facade):
    print(facade.operation())
if __name__ == "__main__":
    sub_system1 = SubSystem1()
    sub_system2 = SubSystem2()
    facade = Facade(sub_system1, sub_system2)
    client_code(facade)


