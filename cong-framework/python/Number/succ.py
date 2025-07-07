
from core.function import FunctionSpecification, FunctionFromSpec
from core import Bind



class SpecSucc(FunctionSpecification):

    def __init__(self):
        super().__init__(
            "succ",
            """""",
            [ConceptNatural.instance()],
            ConceptInteger.instance(),
            [
            ]
        )

def succ(*args):
    return Bind(FunctionFromSpec(SpecSucc()), *args)

