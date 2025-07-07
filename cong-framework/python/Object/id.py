
from core.function import FunctionSpecification, FunctionFromSpec
from core import Bind



class SpecId(FunctionSpecification):

    def __init__(self):
        super().__init__(
            "id",
            """""",
            [ConceptObject.instance()],
            ConceptObject.instance(),
            [
                GenericFunction(
                    lambda a: 
                )
            ]
        )

def id(*args):
    return Bind(FunctionFromSpec(SpecId()), *args)

