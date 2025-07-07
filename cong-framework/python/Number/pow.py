
from core.function import FunctionSpecification, FunctionFromSpec
from core import Bind



class SpecPow(FunctionSpecification):

    def __init__(self):
        super().__init__(
            "pow",
            """""",
            [ConceptNumber.instance(), ConceptInteger.instance()],
            ConceptNumber.instance(),
            [
            ]
        )

def pow(*args):
    return Bind(FunctionFromSpec(SpecPow()), *args)

