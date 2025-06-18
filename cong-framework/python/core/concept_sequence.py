
from .concept import Concept
from .function import FunctionSpecification

class ConceptObject(Concept):
    _instance = None
    
    def __init__(self):
        super().__init__("Object", "Basisklasse")
    
    @classmethod
    def instance(cls):
        if cls._instance is None:
            cls._instance = cls()
        return cls._instance

class ConceptNumber(Concept):
    _instance = None
    
    def __init__(self):
        super().__init__("Number", "Zahl", [ConceptObject.instance()])
    
    @classmethod
    def instance(cls):
        if cls._instance is None:
            cls._instance = cls()
        return cls._instance

class ConceptSequence(Concept):
    
    _instance = None
    
    def __init__(self):
        super().__init__("Sequence", "Eine geordnete Sammlung von Elementen", [ConceptObject.instance()])
    
    @classmethod
    def instance(cls):
        if cls._instance is None:
            cls._instance = cls()
        return cls._instance


class SpecItemAt(FunctionSpecification):
    def __init__(self):
        super().__init__(
            "itemAt", 
            "Gibt das Element an einem bestimmten Index in einer Sequenz zurück.", 
            [ConceptSequence.instance(), 
                ConceptNumber.instance()], 
            ConceptObject.instance())


class SpecReplaceItemAt(FunctionSpecification):
    def __init__(self):
        super().__init__(
            "replaceItemAt", 
            "Replaces an item at a specific index in a sequence with a new value.", 
            [ConceptSequence.instance(), 
                ConceptNumber.instance(), 
                ConceptObject.instance()],
            ConceptObject.instance())