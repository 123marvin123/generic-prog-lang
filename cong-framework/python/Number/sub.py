
from core.function import FunctionSpecification, FunctionFromSpec
from core import Bind



class SpecSub(FunctionSpecification):

    def __init__(self):
        super().__init__(
            "sub",
            """""",
            [ConceptNumber.instance(), ConceptNumber.instance()],
            ConceptNumber.instance(),
            [
            ]
        )

def sub(*args):
    return Bind(FunctionFromSpec(SpecSub()), *args)

