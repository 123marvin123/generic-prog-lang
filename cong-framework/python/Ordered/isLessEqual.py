
from core.function import FunctionSpecification, FunctionFromSpec
from core import Bind



class SpecIsLessEqual(FunctionSpecification):

    def __init__(self):
        super().__init__(
            "isLessEqual",
            """""",
            [ConceptOrdered.instance(), ConceptOrdered.instance()],
            ConceptBoolean.instance(),
            [
            ]
        )

def isLessEqual(*args):
    return Bind(FunctionFromSpec(SpecIsLessEqual()), *args)

