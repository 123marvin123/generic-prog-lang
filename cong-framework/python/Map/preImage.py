
from core.function import FunctionSpecification, FunctionFromSpec
from core import Bind



class SpecPreImage(FunctionSpecification):

    def __init__(self):
        super().__init__(
            "preImage",
            """pre-image of p(2) under p(1)""",
            [ConceptMap.instance(), ConceptSet.instance()],
            ConceptSet.instance(),
            [
            ]
        )

def preImage(*args):
    return Bind(FunctionFromSpec(SpecPreImage()), *args)

