
from core.function import FunctionSpecification, FunctionFromSpec
from core import Bind



class SpecCodomain(FunctionSpecification):

    def __init__(self):
        super().__init__(
            "codomain",
            """codomain of p(1)""",
            [ConceptMap.instance()],
            ConceptSet.instance(),
            [
            ]
        )

def codomain(*args):
    return Bind(FunctionFromSpec(SpecCodomain()), *args)

