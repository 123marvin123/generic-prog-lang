
from core.function import FunctionSpecification, FunctionFromSpec
from core import Bind



class SpecDiv(FunctionSpecification):

    def __init__(self):
        super().__init__(
            "div",
            """""",
            [ConceptNumber.instance(), ConceptNumber.instance()],
            ConceptNumber.instance(),
            [
            ]
        )

def div(*args):
    return Bind(FunctionFromSpec(SpecDiv()), *args)

