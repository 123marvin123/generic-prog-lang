
from core.function import FunctionSpecification, FunctionFromSpec
from core import Bind



class SpecEmbed(FunctionSpecification):

    def __init__(self):
        super().__init__(
            "embed",
            """replace p(1) by p(2) on domain of p(2)""",
            [ConceptMap.instance(), ConceptMap.instance()],
            ConceptMap.instance(),
            [
            ]
        )

def embed(*args):
    return Bind(FunctionFromSpec(SpecEmbed()), *args)

