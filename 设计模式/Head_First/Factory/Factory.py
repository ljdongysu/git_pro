# # from __feature__ import annotations
# from abc import ABC, abstractclassmethod
# class Product(ABC):
#     @abstractclassmethod
#     def operation(self)->str:
#         pass
# class ConcreteProduct1(Product):
#     def operation(self)->str:
#         return "{Result of ConcreteProduct1}"

# class ConcreteProduct2(Product):
#     def operation(self)->str:
#         return "{Result of the COncreteProduct2}"
# class Creator(ABC):
#     @abstractclassmethod
#     def factory_method(self):
#         pass
#     def some_operation(self)->str:
#         product = self.factory_method()
#         result = f"Creator: The same creator's code has just worked woth {product.operation()}"
#         # result = f"Creator: The same creator's code has just worked with {product.operation()}"
#         return result
# class ConcreteCreator1(Creator):
#     def factory_method(self)->Product:
#         return ConcreteProduct1()
# class ConcreteCreator2(Creator):
#     def factory_method(self)->Product:
#         return ConcreteProduct2()



# def client_code(creator:Creator)->None:
#     print(f"Client: I'm not aware of the creator's class, but it still works.\n"
#           f"{creator.some_operation()}", end="")

# if __name__ == "__main__":
#     print("App: Launched with the ConcreteCreator1.")
#     client_code(ConcreteCreator1())
#     print("\n")

#     print("App: Launched with the ConcreteCreator2.")
#     client_code(ConcreteCreator2())



#!/usr/bin/python
# -*- coding: UTF-8 -*-
 
class Point:
   def __init__( self, x=0, y=0):
      self.x = x
      self.y = y
   def __del__(self):
      class_name = self.__class__.__name__
      print (class_name, "销毁")
 
pt1 = Point()
pt2 = Point()
pt3 = pt1
print (id(pt1), id(pt2), id(pt3)) # 打印对象的id
del pt1
del pt2
del pt3
