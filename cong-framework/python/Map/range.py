
from core.function import FunctionSpecification, FunctionFromSpec
from core import Bind



class SpecRange(FunctionSpecification):

    def __init__(self):
        super().__init__(
            "range",
            """range of p(1)""",
            [ConceptMap.instance()],
            ConceptSet.instance(),
            [
                GenericFunction(
                    lambda p1: 
                )
            ]
        )

def range(*args):
    return Bind(FunctionFromSpec(SpecRange()), *args)

