
from core.function import FunctionSpecification, FunctionFromSpec
from core import Bind



class SpecImply(FunctionSpecification):

    def __init__(self):
        super().__init__(
            "imply",
            """p(1) $\\implies$ p(2) (logical implication)""",
            [ConceptBoolean.instance(), ConceptBoolean.instance()],
            ConceptBoolean.instance(),
            [
            ]
        )

def imply(*args):
    return Bind(FunctionFromSpec(SpecImply()), *args)

