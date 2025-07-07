
from core.function import FunctionSpecification, FunctionFromSpec
from core import Bind



class SpecMul(FunctionSpecification):

    def __init__(self):
        super().__init__(
            "mul",
            """""",
            [ConceptNumber.instance(), ConceptNumber.instance()],
            ConceptNumber.instance(),
            [
            ]
        )

def mul(*args):
    return Bind(FunctionFromSpec(SpecMul()), *args)

