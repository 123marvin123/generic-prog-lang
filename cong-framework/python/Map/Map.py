
from Object.Object import ConceptObject

from core.concept import Concept

class ConceptMap(Concept):

    _instance = None

    def __init__(self):
        super().__init__(
            "Map", 
            """""",
            [ConceptObject.instance()]
        )
    
    @classmethod
    def instance(cls):
        if cls._instance is None:
            cls._instance = cls()
        return cls._instance


from core.function import FunctionSpecification, FunctionFromSpec
from core import Bind



class SpecMap(FunctionSpecification):

    def __init__(self):
        super().__init__(
            "map",
            """map of (all elements of) p(1) to p(2)""",
            [ConceptSet.instance(), ConceptObject.instance()],
            ConceptMap.instance(),
            [
            ]
        )

def map(*args):
    return Bind(FunctionFromSpec(SpecMap()), *args)

