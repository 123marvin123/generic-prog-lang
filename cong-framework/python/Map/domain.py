
from core.function import FunctionSpecification, FunctionFromSpec
from core import Bind



class SpecDomain(FunctionSpecification):

    def __init__(self):
        super().__init__(
            "domain",
            """domain of p(1)""",
            [ConceptMap.instance()],
            ConceptSet.instance(),
            [
            ]
        )

def domain(*args):
    return Bind(FunctionFromSpec(SpecDomain()), *args)

