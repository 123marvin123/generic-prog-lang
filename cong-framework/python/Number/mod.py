
from core.function import FunctionSpecification, FunctionFromSpec
from core import Bind



class SpecMod(FunctionSpecification):

    def __init__(self):
        super().__init__(
            "mod",
            """""",
            [ConceptNumber.instance(), ConceptNumber.instance()],
            ConceptNumber.instance(),
            [
            ]
        )

def mod(*args):
    return Bind(FunctionFromSpec(SpecMod()), *args)

