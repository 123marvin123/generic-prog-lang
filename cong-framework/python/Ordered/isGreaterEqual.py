
from core.function import FunctionSpecification, FunctionFromSpec
from core import Bind



class SpecIsGreaterEqual(FunctionSpecification):

    def __init__(self):
        super().__init__(
            "isGreaterEqual",
            """""",
            [ConceptOrdered.instance(), ConceptOrdered.instance()],
            ConceptBoolean.instance(),
            [
            ]
        )

def isGreaterEqual(*args):
    return Bind(FunctionFromSpec(SpecIsGreaterEqual()), *args)

