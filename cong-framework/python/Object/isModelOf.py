from Boolean.Boolean import ConceptBoolean
from Object.Object import ConceptObject
from core.function import FunctionSpecification, FunctionFromSpec, GenericFunction
from core import Bind
from core.primitive import Boolean


def _is_concept_parent_recursive(satisfied_concept, target_concept):
    """Rekursiv prüfen ob target_concept ein Elternkonzept von satisfied_concept ist"""
    if satisfied_concept == target_concept:
        return True

    # Prüfe ob satisfied_concept Bases hat und iteriere durch sie
    if hasattr(satisfied_concept, 'bases'):
        try:
            for base in satisfied_concept.bases:
                if _is_concept_parent_recursive(base, target_concept):
                    return True
        except (TypeError, AttributeError):
            # Falls bases nicht iterierbar ist
            pass

    return False


def _check_is_model_of(obj, concept):
    """Prüfe ob obj das concept modelliert"""
    # Extrahiere das echte Konzept aus einem _ConceptWrapper falls nötig
    if hasattr(concept, 'concept'):
        concept = concept.concept()

    # Prüfe ob obj ein Satisfies-Attribut hat
    if not hasattr(obj, 'Satisfies'):
        return Boolean(False)

    try:
        # Iteriere durch alle Konzepte in Satisfies
        for satisfied_concept in obj.Satisfies:
            if _is_concept_parent_recursive(satisfied_concept, concept):
                return Boolean(True)
    except (TypeError, AttributeError):
        # Falls Satisfies nicht iterierbar ist
        return Boolean(False)

    return Boolean(False)


class SpecIsModelOf(FunctionSpecification):

    def __init__(self):
        super().__init__(
            "isModelOf",
            """does object p(1) model concept p(2)?""",
            [ConceptObject.instance(), ConceptObject.instance()],
            ConceptBoolean.instance(),
            [
                GenericFunction(_check_is_model_of)
            ]
        )


def isModelOf(*args):
    spec = SpecIsModelOf()

    for x in spec.preconditions:
        if not x(*args):
            raise RuntimeError(f"Precondition {x} not satisfied for isModelOf with args {args}")

    return Bind(FunctionFromSpec(spec), *args)
