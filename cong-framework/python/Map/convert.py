
from core.function import FunctionSpecification, FunctionFromSpec
from core import Bind



class SpecConvert(FunctionSpecification):

    def __init__(self):
        super().__init__(
            "convert",
            """(multi) set formed by applying p(1) to each element of p(2)""",
            [ConceptMap.instance(), ConceptSet.instance()],
            ConceptSet.instance(),
            [
            ]
        )

def convert(*args):
    return Bind(FunctionFromSpec(SpecConvert()), *args)

