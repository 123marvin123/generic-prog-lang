
from core.function import FunctionSpecification, FunctionFromSpec
from core import Bind



class SpecFilter(FunctionSpecification):

    def __init__(self):
        super().__init__(
            "filter",
            """set of elements of p(1) for which predicate p(2) holds""",
            [ConceptSet.instance(), ConceptMap.instance()],
            ConceptSet.instance(),
            [
            ]
        )

def filter(*args):
    return Bind(FunctionFromSpec(SpecFilter()), *args)

