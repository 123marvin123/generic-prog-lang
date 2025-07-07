
from core.function import FunctionSpecification, FunctionFromSpec
from core import Bind



class SpecPred(FunctionSpecification):

    def __init__(self):
        super().__init__(
            "pred",
            """""",
            [ConceptObject.instance()],
            ConceptObject.instance(),
            [
            ]
        )

def pred(*args):
    return Bind(FunctionFromSpec(SpecPred()), *args)

