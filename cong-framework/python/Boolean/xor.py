
from core.function import FunctionSpecification, FunctionFromSpec
from core import Bind



class SpecXor(FunctionSpecification):

    def __init__(self):
        super().__init__(
            "xor",
            """""",
            [ConceptBoolean.instance(), ConceptBoolean.instance()],
            ConceptBoolean.instance(),
            [
            ]
        )

def xor(*args):
    return Bind(FunctionFromSpec(SpecXor()), *args)

