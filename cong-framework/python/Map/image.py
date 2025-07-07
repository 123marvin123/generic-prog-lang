
from core.function import FunctionSpecification, FunctionFromSpec
from core import Bind



class SpecImage(FunctionSpecification):

    def __init__(self):
        super().__init__(
            "image",
            """image of p(2) under p(1)""",
            [ConceptMap.instance(), ConceptSet.instance()],
            ConceptSet.instance(),
            [
            ]
        )

def image(*args):
    return Bind(FunctionFromSpec(SpecImage()), *args)

