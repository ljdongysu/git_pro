# from abc import ABC,abstractclassmethod
# class Component(ABC):

#     @property
#     def parent(self):
#         return self._parent

#     @parent.setter
#     def parent(self,component)->None:
#         self._parent = component

#     def add(self,component)->None:
#         pass

#     def remove(self,component)->None:
#         pass

#     @abstractclassmethod
#     def operation(self)->str:
#         pass

#     def is_composite(slef)->bool:
#         return False

# class Leaf(Component):
#     def __init__(self)->None:
#         pass
#     def operation(self)->str:
#         return "Leaf"

# class Composite(Component):
#     # 
#     def __init__(self)->None:
#         self._children:list[Component] = []
#         pass
#     def add(self,component:Component)->None:
#         self._children.append(component)
#         component.parent = self
    
#     def remove(self,component:Component)->None:
#         self._children.remove(component)
#         component.parent = None
    
#     def operation(self)->str:
#         result = []
#         for child in self._children:
#             result.append(child.operation())
#         return f"Branch({'+'.join(result)})"
#     def is_composite(slef)->bool:
#         return True

# def client_code(compenent:Composite)->None:
#     print("RESULTL: " + compenent.operation())

# def client_code_1(component1:Component, component2:Component)->None:
#     if (component1.is_composite()):
#         component1.add(component2)
#     print("RESULTL: " + component1.operation())

# if __name__ == "__main__":
#     simple = Leaf()
#     print("Client: I've got a simple component:")
#     client_code(simple)
#     print("\n")

#     tree = Composite()

#     branch1 = Composite()
#     branch1.add(Leaf())
#     branch1.add(Leaf())

#     branch2 = Composite()
#     branch2.add(Leaf())

#     tree.add(branch1)
#     tree.add(branch2)

#     print("Client: Now I've got a composite tree:")
#     client_code(tree)
#     print("\n")

#     print("Client: I don't need to check the components classes even when managing the tree:")
#     client_code_1(tree, simple)


from __future__ import annotations
from abc import ABC, abstractmethod
from typing import List


class Component(ABC):
    """
    The base Component class declares common operations for both simple and
    complex objects of a composition.
    """

    @property
    def parent(self) -> Component:
        return self._parent

    @parent.setter
    def parent(self, parent: Component):
        """
        Optionally, the base Component can declare an interface for setting and
        accessing a parent of the component in a tree structure. It can also
        provide some default implementation for these methods.
        """

        self._parent = parent

    """
    In some cases, it would be beneficial to define the child-management
    operations right in the base Component class. This way, you won't need to
    expose any concrete component classes to the client code, even during the
    object tree assembly. The downside is that these methods will be empty for
    the leaf-level components.
    """

    def add(self, component: Component) -> None:
        pass

    def remove(self, component: Component) -> None:
        pass

    def is_composite(self) -> bool:
        """
        You can provide a method that lets the client code figure out whether a
        component can bear children.
        """

        return False

    @abstractmethod
    def operation(self) -> str:
        """
        The base Component may implement some default behavior or leave it to
        concrete classes (by declaring the method containing the behavior as
        "abstract").
        """

        pass
