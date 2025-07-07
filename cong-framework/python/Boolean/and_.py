
from core.function import FunctionSpecification, FunctionFromSpec
from core import Bind



class SpecAnd_(FunctionSpecification):

    def __init__(self):
        super().__init__(
            "and_",
            """""",
            [ConceptBoolean.instance(), ConceptBoolean.instance()],
            ConceptBoolean.instance(),
            [
            ]
        )

def and_(*args):
    return Bind(FunctionFromSpec(SpecAnd_()), *args)

