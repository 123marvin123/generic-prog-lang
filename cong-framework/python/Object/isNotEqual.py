
from core.function import FunctionSpecification, FunctionFromSpec
from core import Bind



class SpecIsNotEqual(FunctionSpecification):

    def __init__(self):
        super().__init__(
            "isNotEqual",
            """""",
            [ConceptObject.instance(), ConceptObject.instance()],
            ConceptBoolean.instance(),
            [
                GenericFunction(
                    lambda a, b: 
                )
            ]
        )

def isNotEqual(*args):
    return Bind(FunctionFromSpec(SpecIsNotEqual()), *args)

