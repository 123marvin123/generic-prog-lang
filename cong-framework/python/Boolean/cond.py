
from core.function import FunctionSpecification, FunctionFromSpec
from core import Bind



class SpecCond(FunctionSpecification):

    def __init__(self):
        super().__init__(
            "cond",
            """p(2) if p(1), else p(3)""",
            [ConceptBoolean.instance(), ConceptObject.instance(), ConceptObject.instance()],
            ConceptObject.instance(),
            [
            ]
        )

def cond(*args):
    return Bind(FunctionFromSpec(SpecCond()), *args)

