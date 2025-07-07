
from core.function import FunctionSpecification, FunctionFromSpec
from core import Bind



class SpecApplyFun(FunctionSpecification):

    def __init__(self):
        super().__init__(
            "applyFun",
            """applies p(1) to p(2)""",
            [ConceptMap.instance(), ConceptObject.instance()],
            ConceptObject.instance(),
            [
            ]
        )

def applyFun(*args):
    return Bind(FunctionFromSpec(SpecApplyFun()), *args)

