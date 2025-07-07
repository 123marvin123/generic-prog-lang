

from core.concept import Concept

class ConceptObject(Concept):

    _instance = None

    def __init__(self):
        super().__init__(
            "Object", 
            """""",
            []
        )
    
    @classmethod
    def instance(cls):
        if cls._instance is None:
            cls._instance = cls()
        return cls._instance

