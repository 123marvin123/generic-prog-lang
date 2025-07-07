
from Ordered.Ordered import ConceptOrdered
from Number.Natural import ConceptNatural

from core.concept import Concept

class ConceptInteger(Concept):

    _instance = None

    def __init__(self):
        super().__init__(
            "Integer", 
            """integer number""",
            [ConceptOrdered.instance(),ConceptNatural.instance()]
        )
    
    @classmethod
    def instance(cls):
        if cls._instance is None:
            cls._instance = cls()
        return cls._instance

