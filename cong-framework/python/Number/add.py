
from core.function import FunctionSpecification, FunctionFromSpec
from core import Bind



class SpecAdd(FunctionSpecification):

    def __init__(self):
        super().__init__(
            "add",
            """""",
            [ConceptNumber.instance(), ConceptNumber.instance()],
            ConceptNumber.instance(),
            [
            ]
        )

def add(*args):
    return Bind(FunctionFromSpec(SpecAdd()), *args)

