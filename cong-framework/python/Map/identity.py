
from core.function import FunctionSpecification, FunctionFromSpec
from core import Bind



class SpecIdentity(FunctionSpecification):

    def __init__(self):
        super().__init__(
            "identity",
            """map of (all elements of) p(1) to themselves""",
            [ConceptSet.instance()],
            ConceptMap.instance(),
            [
            ]
        )

def identity(*args):
    return Bind(FunctionFromSpec(SpecIdentity()), *args)

