
from core.function import FunctionSpecification, FunctionFromSpec
from core import Bind



class SpecLeftDiff(FunctionSpecification):

    def __init__(self):
        super().__init__(
            "leftDiff",
            """(left-side) difference of p(1) and p(2)""",
            [ConceptMap.instance(), ConceptMap.instance()],
            ConceptMap.instance(),
            [
            ]
        )

def leftDiff(*args):
    return Bind(FunctionFromSpec(SpecLeftDiff()), *args)

