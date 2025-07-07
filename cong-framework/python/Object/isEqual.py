
from core.function import FunctionSpecification, FunctionFromSpec
from core import Bind



class SpecIsEqual(FunctionSpecification):

    def __init__(self):
        super().__init__(
            "isEqual",
            """""",
            [ConceptObject.instance(), ConceptObject.instance()],
            ConceptBoolean.instance(),
            [
            ]
        )

def isEqual(*args):
    return Bind(FunctionFromSpec(SpecIsEqual()), *args)

