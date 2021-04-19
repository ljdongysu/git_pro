# class SharedState:
#     def __init__(self,brand:str, color:str, model:str)->None:
#         self._brach = brand
#         self._color = color
#         self._model = model

#     def operation(self)->str:
#         return self._brach + "_" + self._color + "_" + self._model

        
# class UniqueState:
#     def __init__(self, owner:str, plates:str)->None:
#         self._owner = owner
#         self._plates = plates

#     def operation(self)->str:
#         return self._owner + '_' + self._plates
# class FlyWeights:
#     def __init__(self, shared_state:SharedState)->None:
#         self._shared_state = shared_state
    
#     def shared_state(self)->SharedState:
#         return self._shared_state

#     def operation(self, unique_state:UniqueState)->None:
#         print("Flyweight: Displaying shared (", self._shared_state.operation(), ") and unique (" ,unique_state.operation(),") state.\n")

# class FlyweightFactory:
#     def __init__(self,flywights:list)->None:
#         self._flyweights = {}
#         for member in flywights:
#             member = SharedState(member.__iter__())
#             flyweight = FlyWeights(member)
#             self._flyweights[self.get_key(flyweight.shared_state())] = flyweight
    
#     def get_key(self,ss:SharedState)->str:
#         return ss._brand + "_" + ss._model + "_" + ss._color
    
#     def get_flyweight(self, shared_state:SharedState)->SharedState:
#         keyvalue = shared_state.operation()                                          # change to self.get_key(shared_state)
#         if (keyvalue in self._flyweights):
#             print("FlyweightFactory: Reusing existing flyweight.\n")
#         else:
#             self._flyweights[keyvalue] = shared_state
#             print("FlyweightFactory: Can't find a flyweight, creating new one.\n")
#         return self._flyweights[keyvalue]
#     def list_flyweights(self)->None:
#         for key_value in self._flyweights:
#             print(self._flyweights[key_value].operation())
    
# def add_car_to_data(ff:FlyweightFactory, owner:str, plates:str, brach:str, model:str, coler:str)->None:
#     shared_state = SharedState(brach,coler,model)
#     flyweight = ff.get_flyweight(shared_state)
#     unique_state = UniqueState(owner,plates)
#     flyweight.operation(unique_state)

# if __name__ == "__main__":
#     fly_weight_facetory = FlyweightFactory([["Chevrolet", "Camaro2018", "pink"], ["Mercedes Benz", "C300", "black"], ["Mercedes Benz", "C500", "red"], ["BMW", "M5", "red"], ["BMW", "X6", "white"]])



import json
from typing import Dict


class Flyweight():
    """
    The Flyweight stores a common portion of the state (also called intrinsic
    state) that belongs to multiple real business entities. The Flyweight
    accepts the rest of the state (extrinsic state, unique for each entity) via
    its method parameters.
    """

    def __init__(self, shared_state: str) -> None:
        self._shared_state = shared_state

    def operation(self, unique_state: str) -> None:
        s = json.dumps(self._shared_state)
        u = json.dumps(unique_state)
        print(f"Flyweight: Displaying shared ({s}) and unique ({u}) state.", end="")


class FlyweightFactory():
    """
    The Flyweight Factory creates and manages the Flyweight objects. It ensures
    that flyweights are shared correctly. When the client requests a flyweight,
    the factory either returns an existing instance or creates a new one, if it
    doesn't exist yet.
    """

    _flyweights: Dict[str, Flyweight] = {}

    def __init__(self, initial_flyweights: Dict) -> None:
        for state in initial_flyweights:
            self._flyweights[self.get_key(state)] = Flyweight(state)

    def get_key(self, state: Dict) -> str:
        """
        Returns a Flyweight's string hash for a given state.
        """

        return "_".join(sorted(state))

    def get_flyweight(self, shared_state: Dict) -> Flyweight:
        """
        Returns an existing Flyweight with a given state or creates a new one.
        """

        key = self.get_key(shared_state)

        if not self._flyweights.get(key):
            print("FlyweightFactory: Can't find a flyweight, creating new one.")
            self._flyweights[key] = Flyweight(shared_state)
        else:
            print("FlyweightFactory: Reusing existing flyweight.")

        return self._flyweights[key]

    def list_flyweights(self) -> None:
        count = len(self._flyweights)
        print(f"FlyweightFactory: I have {count} flyweights:")
        print("\n".join(map(str, self._flyweights.keys())), end="")


def add_car_to_police_database(
    factory: FlyweightFactory, plates: str, owner: str,
    brand: str, model: str, color: str
) -> None:
    print("\n\nClient: Adding a car to database.")
    flyweight = factory.get_flyweight([brand, model, color])
    # The client code either stores or calculates extrinsic state and passes it
    # to the flyweight's methods.
    flyweight.operation([plates, owner])


if __name__ == "__main__":
    """
    The client code usually creates a bunch of pre-populated flyweights in the
    initialization stage of the application.
    """

    factory = FlyweightFactory([
        ["Chevrolet", "Camaro2018", "pink"],
        ["Mercedes Benz", "C300", "black"],
        ["Mercedes Benz", "C500", "red"],
        ["BMW", "M5", "red"],
        ["BMW", "X6", "white"],
    ])

    factory.list_flyweights()

    add_car_to_police_database(
        factory, "CL234IR", "James Doe", "BMW", "M5", "red")

    add_car_to_police_database(
        factory, "CL234IR", "James Doe", "BMW", "X1", "red")

    print("\n")

    factory.list_flyweights()