from .exp import Exp
from .base import Base
from .val import Val

class Concept:
    
    def __init__(self, name, description=None, bases=None):
        self.name = name
        self.description = description or ""
        self.bases = bases or []
        
    def __str__(self):
        base_str = ", ".join(base.name for base in self.bases)
        if base_str:
            return f"Concept({self.name}, bases=[{base_str}])"
        else:
            return f"Concept({self.name})"
        
    def __repr__(self):
        return self.__str__()

class _ConceptWrapper(Val):
    def __init__(self, concept):
        self._concept = concept

    def concept(self):
        return self._concept

def ConceptWrapper(concept):
    if not isinstance(concept, Concept):
        raise TypeError("Das Konzept muss eine Instanz der Klasse Concept sein.")
    return Exp(_ConceptWrapper(concept))

def implements(obj_type, concept):
    if not isinstance(concept, Concept):
        raise TypeError("Das Konzept muss eine Instanz der Klasse Concept sein.")

    while hasattr(obj_type, 'impl'):
        obj_type = obj_type.impl

    if hasattr(obj_type, '__class__') and hasattr(obj_type.__class__, '__bases__'):
        for base in obj_type.__class__.__bases__:
            if hasattr(base, 'BASES'):
                for base_concept in base.BASES:
                    if hasattr(base_concept, 'get') and base_concept.get() == concept:
                        return True
                    elif base_concept == concept:
                        return True

    if hasattr(obj_type, 'BASES'):
        bases = obj_type.BASES
        for base in bases:
            if hasattr(base, 'get') and base.get() == concept:
                return True
            elif base == concept:
                return True

    for base_concept in concept.bases:
        if implements(obj_type, base_concept):
            return True
            
    return False
