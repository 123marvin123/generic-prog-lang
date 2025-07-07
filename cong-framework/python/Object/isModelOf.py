
from core.function import FunctionSpecification, FunctionFromSpec
from core import Bind



class SpecIsModelOf(FunctionSpecification):

    def __init__(self):
        super().__init__(
            "isModelOf",
            """does object p(1) model concept p(2)?""",
            [ConceptObject.instance(), ConceptObject.instance()],
            ConceptBoolean.instance(),
            [
            ]
        )

def isModelOf(*args):
    return Bind(FunctionFromSpec(SpecIsModelOf()), *args)

