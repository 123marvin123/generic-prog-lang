
from core.function import FunctionSpecification, FunctionFromSpec
from core import Bind



class SpecIsLess(FunctionSpecification):

    def __init__(self):
        super().__init__(
            "isLess",
            """""",
            [ConceptOrdered.instance(), ConceptOrdered.instance()],
            ConceptBoolean.instance(),
            [
            ]
        )

def isLess(*args):
    return Bind(FunctionFromSpec(SpecIsLess()), *args)

