
from core.function import FunctionSpecification, FunctionFromSpec
from core import Bind



class SpecAssign(FunctionSpecification):

    def __init__(self):
        super().__init__(
            "assign",
            """p(2) (the second argument) - side effect: if p(1) is modifiable, it will also have the value of p(2)""",
            [ConceptObject.instance(), ConceptObject.instance()],
            ConceptObject.instance(),
            [
            ]
        )

def assign(*args):
    return Bind(FunctionFromSpec(SpecAssign()), *args)

