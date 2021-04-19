from abc import ABC,abstractmethod
class Component(ABC):
    def __init__(self):
        pass
    
    @abstractmethod
    def operation(self)->str:
        pass

class SubComponent(Component):
    def __init__(self):
        pass

    def operation(self)->str:
        return "SubComponent"

class ComponentDecorator(Component):
    def __init__(self,component:Component)->None:
        self._component = component
    
    def operation(self)->str:
        return "Decorator" + self._component.operation() 

class ComponentDecorator1(ComponentDecorator):
    def __init__(self,component:Component)->None:
        self._component = component

    def operation(self)->str:
        return "ComponentDecorator1" + self._component.operation() 



class ComponentDecorator2(ComponentDecorator):
    def __init__(self,component:Component)->None:
        self._component = component

    def operation(self)->str:
        return "ComponentDecorator2" + self._component.operation() 

if __name__ == "__main__":
    subc = SubComponent()
    print(subc.operation())
    cd = ComponentDecorator(subc)
    cd1 = ComponentDecorator1(cd)
    cd2 = ComponentDecorator2(cd1)

    print(cd.operation())
    print(cd1.operation())
    print(cd2.operation())器