
from core.function import FunctionSpecification, FunctionFromSpec
from core import Bind



class SpecCompose(FunctionSpecification):

    def __init__(self):
        super().__init__(
            "compose",
            """composition of p(1) and p(2)""",
            [ConceptMap.instance(), ConceptMap.instance()],
            ConceptMap.instance(),
            [
            ]
        )

def compose(*args):
    return Bind(FunctionFromSpec(SpecCompose()), *args)

