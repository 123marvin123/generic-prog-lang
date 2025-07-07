
from Ordered.Ordered import ConceptOrdered
from Number.Number import ConceptNumber

from core.concept import Concept

class ConceptRational(Concept):

    _instance = None

    def __init__(self):
        super().__init__(
            "Rational", 
            """rational number""",
            [ConceptOrdered.instance(),ConceptNumber.instance()]
        )
    
    @classmethod
    def instance(cls):
        if cls._instance is None:
            cls._instance = cls()
        return cls._instance

