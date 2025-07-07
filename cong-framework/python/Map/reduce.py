
from core.function import FunctionSpecification, FunctionFromSpec
from core import Bind



class SpecReduce(FunctionSpecification):

    def __init__(self):
        super().__init__(
            "reduce",
            """successive application of p(2) to elements of p(1), in arbitrary order, passing on the accumulated result as first argument""",
            [ConceptSet.instance(), ConceptMap.instance()],
            ConceptObject.instance(),
            [
            ]
        )

def reduce(*args):
    return Bind(FunctionFromSpec(SpecReduce()), *args)

