
from core.function import FunctionSpecification, FunctionFromSpec
from core import Bind



class SpecNot_(FunctionSpecification):

    def __init__(self):
        super().__init__(
            "not_",
            """""",
            [ConceptBoolean.instance()],
            ConceptBoolean.instance(),
            [
            ]
        )

def not_(*args):
    return Bind(FunctionFromSpec(SpecNot_()), *args)

