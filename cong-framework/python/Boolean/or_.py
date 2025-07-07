
from core.function import FunctionSpecification, FunctionFromSpec
from core import Bind



class SpecOr_(FunctionSpecification):

    def __init__(self):
        super().__init__(
            "or_",
            """""",
            [ConceptBoolean.instance(), ConceptBoolean.instance()],
            ConceptBoolean.instance(),
            [
            ]
        )

def or_(*args):
    return Bind(FunctionFromSpec(SpecOr_()), *args)

