
from core.function import FunctionSpecification, FunctionFromSpec
from core import Bind



class SpecIsGreater(FunctionSpecification):

    def __init__(self):
        super().__init__(
            "isGreater",
            """""",
            [ConceptOrdered.instance(), ConceptOrdered.instance()],
            ConceptBoolean.instance(),
            [
            ]
        )

def isGreater(*args):
    return Bind(FunctionFromSpec(SpecIsGreater()), *args)

