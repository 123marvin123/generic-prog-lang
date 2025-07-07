
from core.function import FunctionSpecification, FunctionFromSpec
from core import Bind



class SpecLeftIntersection(FunctionSpecification):

    def __init__(self):
        super().__init__(
            "leftIntersection",
            """(left-side) intersection of p(1) and p(2)""",
            [ConceptMap.instance(), ConceptMap.instance()],
            ConceptMap.instance(),
            [
            ]
        )

def leftIntersection(*args):
    return Bind(FunctionFromSpec(SpecLeftIntersection()), *args)

