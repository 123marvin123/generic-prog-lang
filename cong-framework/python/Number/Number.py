
from Object.Object import ConceptObject

from core.concept import Concept

class ConceptNumber(Concept):

    _instance = None

    def __init__(self):
        super().__init__(
            "Number", 
            """""",
            [ConceptObject.instance()]
        )
    
    @classmethod
    def instance(cls):
        if cls._instance is None:
            cls._instance = cls()
        return cls._instance

