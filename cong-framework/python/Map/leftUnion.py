
from core.function import FunctionSpecification, FunctionFromSpec
from core import Bind



class SpecLeftUnion(FunctionSpecification):

    def __init__(self):
        super().__init__(
            "leftUnion",
            """left-side union of p(1) and p(2)""",
            [ConceptMap.instance(), ConceptMap.instance()],
            ConceptMap.instance(),
            [
            ]
        )

def leftUnion(*args):
    return Bind(FunctionFromSpec(SpecLeftUnion()), *args)

